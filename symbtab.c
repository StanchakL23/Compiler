#include "symbtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
static int temp_counter = 0;

// ============ TYPE RECORD OPERATIONS ============

const char* basetype_to_string(BaseType base) {
    switch(base) {
        case INT: return "int";
        case FLOAT: return "float";
        case BOOL: return "bool";
        default: return "unknown";
    }
}

char* type_to_string(TypeRecord *type) {
    if (!type) return strdup("null");
    
    static char buffer[256];
    strcpy(buffer, basetype_to_string(type->base_type));
    
    for (int i = 0; i < type->num_dimensions; i++) {
        char dim[32];
        sprintf(dim, "[%d]", type->dimensions[i]);
        strcat(buffer, dim);
    }
    
    return strdup(buffer);
}

TypeRecord* type_record_create(BaseType base, int *dims, int num_dims) {
    TypeRecord *type = malloc(sizeof(TypeRecord));
    type->base_type = base;
    type->num_dimensions = num_dims;
    
    if (num_dims > 0 && dims != NULL) {
        type->dimensions = malloc(sizeof(int) * num_dims);
        memcpy(type->dimensions, dims, sizeof(int) * num_dims);
    } else {
        type->dimensions = NULL;
    }
    
    return type;
}

// Size calculation function
size_t type_size(TypeRecord *type) {
    if (!type) return 0;
    
    size_t base_size;
    switch (type->base_type) {
        case INT:
            base_size = sizeof(int);
            break;
        case FLOAT:
            base_size = sizeof(double);  // Assignment treats float as double
            break;
        case BOOL:
            base_size = sizeof(int);  // Booleans stored as int
            break;
        default:
            return 0;
    }
    
    // Multiply by all dimensions for arrays
    size_t total_size = base_size;
    for (int i = 0; i < type->num_dimensions; i++) {
        total_size *= type->dimensions[i];
    }
    
    return total_size;
}

// ============ SYMBOL TABLE OPERATIONS ============

// Constructor - equivalent to Env(Env prev)
Env* env_create(Env *prev) {
    Env *env = malloc(sizeof(Env));
    env->prev = prev;
    env->layer = prev->layer + 1;
    env->table = malloc(sizeof(Entry*) * INITIAL_CAPACITY);
    env->size = 0;
    env->capacity = INITIAL_CAPACITY;
    return env;
}

// Overloaded constructor - equivalent to Env()
Env* env_create_global(void) {
    Env *env = malloc(sizeof(Env));
    env->prev = NULL;
    env->layer = 0;
    env->table = malloc(sizeof(Entry*) * INITIAL_CAPACITY);
    env->size = 0;
    env->capacity = INITIAL_CAPACITY;
    return env;
}

// add value to symbol table
void env_put(Env *env, const char *id, TypeRecord *value, bool is_temp) {
    // Check if key already exists, update if so
    for (int i = 0; i < env->size; i++) {
        if (strcmp(env->table[i]->key, id) == 0) {
            env->table[i]->value = value;
            env->table[i]->is_temp = is_temp;
            return;
        }
    }
    
    // Resize if needed
    if (env->size >= env->capacity) {
        env->capacity *= 2;
        env->table = realloc(env->table, sizeof(Entry*) * env->capacity);
    }
    
    // Add new entry
    Entry *entry = malloc(sizeof(Entry));
    entry->key = strdup(id);
    entry->value = value;
    entry->is_temp = is_temp;
    // compute base of this activation record
    long base = calculate_base_address(env);

    // compute offset where the new variable will be placed:
    //this circumvents the fact that the symbol isnt in the env yet.
    // start after control link, then add sizes of already-present variables
    long offset = sizeof(int);
    for (int i = 0; i < env->size; i++) {
        offset += type_size(env->table[i]->value);
    }
    entry->address = base + offset;

    env->table[env->size++] = entry;
}

// Getter - equivalent to get(String id)
TypeRecord* env_get(Env *env, const char *id) {
    Env *temp = env;
    while (temp != NULL) {
        for (int i = 0; i < temp->size; i++) {
            if (strcmp(temp->table[i]->key, id) == 0) {
                return temp->table[i]->value;
            }
        }
        temp = temp->prev;
    }
    return NULL;
}

// Prints the entire trail of scope tables - equivalent to printTrail()
void env_print_trail(Env *env) {
    Env *temp = env;
    while (temp != NULL) {
        printf("Current Scope Layer: %d\n", temp->layer);
        for (int i = 0; i < temp->size; i++) {
            char *type_str = type_to_string(temp->table[i]->value);
            printf("  %s%s: %s (size: %zu bytes)\n", 
                   temp->table[i]->is_temp ? "[TEMP] " : "",
                   temp->table[i]->key, 
                   type_str,
                   type_size(temp->table[i]->value));
            free(type_str);
        }
        temp = temp->prev;
    }
}

// Prints all accessible keys from that scope - equivalent to printTable()
void env_print_table(Env *env) {
    // Track which keys we've already printed
    char **printed_keys = malloc(sizeof(char*) * 100); // simple fixed size
    int printed_count = 0;
    
    Env *temp = env;
    while (temp != NULL) {
        for (int i = 0; i < temp->size; i++) {
            const char *key = temp->table[i]->key;
            
            // Check if already printed
            int found = 0;
            for (int j = 0; j < printed_count; j++) {
                if (strcmp(printed_keys[j], key) == 0) {
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                char *type_str = type_to_string(temp->table[i]->value);
                long offset = calculate_offset(temp, key);
                long address = temp->table[i]->address;
                size_t size = type_size(temp->table[i]->value);

                printf("  %s%s: %s  [offset=%ld, size=%zu, addr=%ld]\n",
                    temp->table[i]->is_temp ? "[TEMP] " : "",
                    key,
                    type_str,
                    offset,
                    size,
                    address);

                    free(type_str);
                    printed_keys[printed_count++] = strdup(key);
                }
        }
        temp = temp->prev;
    }
    
    // Cleanup
    for (int i = 0; i < printed_count; i++) {
        free(printed_keys[i]);
    }
    free(printed_keys);
}

// temp var creation and insertion
char* create_temp(Env *env, BaseType base_type, int *dims, int num_dims) {
    // Generate unique name
    char temp_name[32];
    sprintf(temp_name, "t%d", temp_counter++);
    
    // Create type record
    TypeRecord *type = type_record_create(base_type, dims, num_dims);
    
    // Insert into symbol table (marked as temporary)
    env_put(env, temp_name, type, true);
    
    return strdup(temp_name);
}

//ADDRESS IMPLEMENTATION
// Create a constant address
Address* createIntAddr(int val) {
    Address *addr = malloc(sizeof(Address));
    addr->type = ADDR_CONSTANT;
    addr->data.constant.const_type = CONST_INT;
    addr->data.constant.value.int_val = val;
    return addr;
}

Address* createFloatAddr(double val) {
    Address *addr = malloc(sizeof(Address));
    addr->type = ADDR_CONSTANT;
    addr->data.constant.const_type = CONST_FLOAT;
    addr->data.constant.value.float_val = val;
    return addr;
}

Address* createBoolAddr(bool val) {
    Address *addr = malloc(sizeof(Address));
    addr->type = ADDR_CONSTANT;
    addr->data.constant.const_type = CONST_BOOL;
    addr->data.constant.value.bool_val = val;
    return addr;
}

// Create a variable address
Address* createVarAddr(const char *name, TypeRecord *type) {
    Address *addr = malloc(sizeof(Address));
    addr->type = ADDR_VARIABLE;
    addr->data.variable.name = strdup(name);
    addr->data.variable.type_record = type;
    return addr;
}

// Create a label address
Address* createLabelAddr(const char *label) {
    Address *addr = malloc(sizeof(Address));
    addr->type = ADDR_LABEL;
    addr->data.label.label_name = strdup(label);
    return addr;
}

// Convert address to human-readable string
char* addr_to_string(Address *addr) {
    static char buffer[256];
    
    if (!addr) return strdup("null");
    
    switch (addr->type) {
        case ADDR_CONSTANT:
            switch (addr->data.constant.const_type) {
                case CONST_INT:
                    sprintf(buffer, "%d", addr->data.constant.value.int_val);
                    break;
                case CONST_FLOAT:
                    sprintf(buffer, "%.2f", addr->data.constant.value.float_val);
                    break;
                case CONST_BOOL:
                    sprintf(buffer, "%s", addr->data.constant.value.bool_val ? "true" : "false");
                    break;
            }
            break;
            
        case ADDR_VARIABLE:
            sprintf(buffer, "%s", addr->data.variable.name);
            break;
            
        case ADDR_LABEL:
            sprintf(buffer, "%s", addr->data.label.label_name);
            break;
    }
    
    return strdup(buffer);
}

//INSTRUCTION IMPLEMENTATION
const char* opcode_to_string(OpCode op) {
    switch(op) {
        case OP_ADD: return "ADD";
        case OP_SUB: return "SUB";
        case OP_MUL: return "MUL";
        case OP_DIV: return "DIV";
        case OP_ASSIGN: return "ASSIGN";
        case OP_ARRAY_ACCESS: return "[]";
        case OP_ADDR_CALC: return "ADDR";
        case OP_LOAD: return "LOAD";
        case OP_STORE: return "STORE";
        case OP_LEFT_SHIFT: return "<<";
        case OP_RIGHT_SHIFT: return ">>";
        default: return "UNKNOWN";
    }
}

// Create a new instruction
Instruction* instruction_create(OpCode op, Address *src1, Address *src2, Address *result) {
    Instruction *instr = malloc(sizeof(Instruction));
    instr->op = op;
    instr->src1 = src1;
    instr->src2 = src2;
    instr->result = result;
    instr->next = NULL;
    return instr;
}

// Create intermediate code container
IntermediateCode* intermediate_code_create() {
    IntermediateCode *code = malloc(sizeof(IntermediateCode));
    code->head = NULL;
    code->tail = NULL;
    code->instruction_count = 0;
    return code;
}

// Append an instruction to intermediate code
void intermediate_code_append(IntermediateCode *code, Instruction *instr) {
    if (code->tail == NULL) {
        // First instruction
        code->head = instr;
        code->tail = instr;
    } else {
        // Append to end
        code->tail->next = instr;
        code->tail = instr;
    }
    code->instruction_count++;
}

void intermediate_code_print(IntermediateCode *code) {
    printf("\nIntermediate Code:\n");
    
    Instruction *current = code->head;
    int line = 1;
    
    while (current != NULL) {
        printf("%3d: ", line++);
        
        char *result_str = addr_to_string(current->result);
        char *src1_str = addr_to_string(current->src1);
        char *src2_str = addr_to_string(current->src2);
        
        // Format depends on operation type
        if (current->op == OP_ASSIGN) {
            printf("%s = %s\n", result_str, src1_str);
        } else if (current->op == OP_STORE) { // <-- NEW
            // STORE Source DestinationAddress
            printf("STORE %s %s\n", src1_str, result_str);
        } else if (current->op == OP_LEFT_SHIFT || current->op == OP_RIGHT_SHIFT) {
            // Shift operations
            printf("%s = %s %s %s\n", result_str, src1_str, opcode_to_string(current->op), src2_str);
        } else if (current->src2 != NULL) {
            // Binary operations
            printf("%s = %s %s %s\n", result_str, src1_str, opcode_to_string(current->op), src2_str);
        } else {
            // Other formats
            printf("%s %s %s\n", opcode_to_string(current->op), src1_str, result_str);
        }

        
        
        free(result_str);
        free(src1_str);
        free(src2_str);
        
        current = current->next;
    }
}

BaseType get_address_type(Address *addr) {
    if (!addr) return INT;  
    
    if (addr->type == ADDR_CONSTANT) {
        switch (addr->data.constant.const_type) {
            case CONST_INT: return INT;
            case CONST_FLOAT: return FLOAT;
            case CONST_BOOL: return BOOL;
        }
    } else if (addr->type == ADDR_VARIABLE) {
        if (addr->data.variable.type_record) {
            return addr->data.variable.type_record->base_type;
        }
    }
    
    return INT;  // default
}

// convert addr a from type t to type w
Address* widen(Env *env, Address *addr, BaseType t, BaseType w, IntermediateCode *code) {
    // if types are the same, return address as-is
    if (t == w) {
        return addr;
    }
    
    // If converting int to float
    if (t == INT && w == FLOAT) {
        // Create new temporary of target type
        char *temp_name = create_temp(env, FLOAT, NULL, 0);
        TypeRecord *temp_type = env_get(env, temp_name);
        Address *temp = createVarAddr(temp_name, temp_type);
        
        Instruction *convert = instruction_create(OP_ASSIGN, addr, NULL, temp);
        if (code) {
            intermediate_code_append(code, convert);
        }
        
        return temp;
    }
    
    // Otherwise, error
    fprintf(stderr, "Type error: cannot convert %s to %s\n",
            basetype_to_string(t), basetype_to_string(w));
    return addr;
}

// returns the wider type
BaseType max_type(BaseType t1, BaseType t2) {
    if (t1 == FLOAT || t2 == FLOAT) return FLOAT;
    if (t1 == INT || t2 == INT) return INT;
    return BOOL;
}

// Get element size/width for array type
size_t get_element_width(TypeRecord *type) {
    if (!type) return 0;
    
    size_t base_size;
    switch (type->base_type) {
        case INT: base_size = sizeof(int); break;
        case FLOAT: base_size = sizeof(double); break;
        case BOOL: base_size = sizeof(int); break;
        default: return 0;
    }
    
    return base_size;
}

//NEW FOR ASSIGNMENT 5
long calculate_offset(Env *env, const char *var_name) {
    long offset = sizeof(int);  // control link

    for (int i = 0; i < env->size; i++) {
        if (strcmp(env->table[i]->key, var_name) == 0) {
            return offset;  // found variable, return current offset
        }
        offset += type_size(env->table[i]->value);  // accumulate
    }

    return -1;  // not found in THIS record
}


long calculate_record_length(Env *env) {
    if (env->size == 0) {
        // No variables, just the control link
        return sizeof(int);
    }
    
    long max_end = 0;
    
    for (int i = 0; i < env->size; i++) {
        long offset = calculate_offset(env, env->table[i]->key);
        long size   = type_size(env->table[i]->value);
        long end    = offset + size;
        
        if (end > max_end)
            max_end = end;
    }
    
    return max_end;   // total activation record size
}

long calculate_base_address(Env *env) {
    if (env->prev == NULL)
        return 0;  // global AR sits at address 0

    long parent_base = calculate_base_address(env->prev);
    long parent_len  = calculate_record_length(env->prev);

    return parent_base + parent_len;
}

long calculate_variable_address(Env *env, const char *var_name) {
    Env *temp = env;

    while (temp != NULL) {
        for (int i = 0; i < temp->size; i++) {
            if (strcmp(temp->table[i]->key, var_name) == 0) {
                long base   = calculate_base_address(temp);
                long offset = calculate_offset(temp, var_name);
                return base + offset;
            }
        }
        temp = temp->prev;
    }
    return -1;
}

//NEW: local print function to call on closing of a symbol table to showcase address
void env_print_scope(Env *env) {
    printf("\n=== Closing Scope (layer %d) ===\n", env->layer);
    printf("%-15s %-12s %-8s %-12s\n", 
           "Identifier", "Type", "Size", "Address");

    for (int i = 0; i < env->size; i++) {
        Entry *e = env->table[i];
        if (!e) continue;

        char *type_str = type_to_string(e->value);
        size_t size = type_size(e->value);

        // THIS IS THE REAL ADDRESS YOU WANTED
        long actual_addr = e->address;

        printf("%-15s %-12s %-8zu %-12ld\n",
               e->key, type_str, size, actual_addr);

        free(type_str);
    }

    printf("====================================\n");
}

bool is_power_of_two(int n) {
    if( n <= 0 ) return false;
    return (n & (n - 1)) == 0; //bitwise comparison, if 0100 and 1011, then true.
}

int log2_int(int n) {
    int i = 0;
    while (n > 1) {
        n = n >> 1; //right shift by 1 until n is 0
        i++;
    }
    return i;
}

int is_power_of_two_plus_one(int n) {
    if( n <= 1 ) return -1;
    if( is_power_of_two(n - 1) ) { return log2_int(n - 1); }
    return -1;
}

int is_power_of_two_minus_one(int n) {
    if( n <= 1 ) return -1;
    if( is_power_of_two(n + 1) ) { return log2_int(n + 1); }
    return -1;
}

void strength_reduction(IntermediateCode *code, Env *env) {
    if (!code || !env) return;
    
    Instruction *current = code->head;
    Instruction *prev = NULL;
    
    while (current != NULL) {
        Instruction *next = current->next;
        
        // Case 1 & 3: MUL/DIV by power of 2 → shift
        if ((current->op == OP_MUL || current->op == OP_DIV) && 
            current->src2 && 
            current->src2->type == ADDR_CONSTANT && 
            current->src2->data.constant.const_type == CONST_INT) {
            
            int constant = current->src2->data.constant.value.int_val;
            
            if (is_power_of_two(constant)) {
                int shift_amount = log2_int(constant);
                current->src2->data.constant.value.int_val = shift_amount;
                
                if (current->op == OP_MUL) {
                    current->op = OP_LEFT_SHIFT;
                    printf("Strength reduction: MUL by %d → LEFT_SHIFT by %d\n",
                           constant, shift_amount);
                } else {
                    current->op = OP_RIGHT_SHIFT;
                    printf("Strength reduction: DIV by %d → RIGHT_SHIFT by %d\n",
                           constant, shift_amount);
                }
            }
            // Case 2: MUL by (2^k +/- 1)
            else if (current->op == OP_MUL) {
                int k_plus = is_power_of_two_plus_one(constant);
                int k_minus = is_power_of_two_minus_one(constant);
                
                if (k_plus >= 0 || k_minus >= 0) {
                    int k = (k_plus >= 0) ? k_plus : k_minus;
                    bool is_plus = (k_plus >= 0);
                    
                    // Save original operand
                    Address *original_x = current->src1;
                    
                    // Create temporary for shift result
                    char *temp_name = create_temp(env, get_address_type(original_x), NULL, 0);
                    TypeRecord *temp_type = env_get(env, temp_name);
                    Address *temp_addr = createVarAddr(temp_name, temp_type);
                    
                    // Create shift instruction: t1 = x << k
                    Address *shift_const = createIntAddr(k);
                    Instruction *shift_instr = instruction_create(
                        OP_LEFT_SHIFT, 
                        original_x,
                        shift_const,
                        temp_addr
                    );
                    
                    // Insert shift before current
                    shift_instr->next = current;
                    if (prev) {
                        prev->next = shift_instr;
                    } else {
                        code->head = shift_instr;
                    }
                    code->instruction_count++;
                    
                    // Transform current to: result = t1 +/- x
                    if (is_plus) {
                        current->op = OP_ADD;
                        printf("Strength reduction: MUL by %d (2^%d+1) → SHIFT + ADD\n",
                               constant, k);
                    } else {
                        current->op = OP_SUB;
                        printf("Strength reduction: MUL by %d (2^%d-1) → SHIFT + SUB\n",
                               constant, k);
                    }
                    
                    current->src1 = temp_addr;
                    current->src2 = original_x;
                    
                    prev = shift_instr;
                }
            }
        }
        
        if (prev != current) {
            prev = current;
        }
        current = next;
    }
}