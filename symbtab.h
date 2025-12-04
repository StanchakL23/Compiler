#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdbool.h>
#include <stddef.h>  // for size_t

// Type record: stores base type and array dimensions
typedef enum {
    INT,
    FLOAT,
    BOOL
} BaseType;

typedef struct {
    BaseType base_type;
    int *dimensions;      
    int num_dimensions;   
} TypeRecord;

// Entry in the hash table
typedef struct {
    char *key;            // identifier name
    TypeRecord *value;    // type info
    bool is_temp;
    long address;
} Entry;

// Symbol table (Env equivalent)
typedef struct Env {
    int layer;
    struct Env *prev;
    Entry **table;        // dynamic array of entries
    int size;             // current number of entries
    int capacity;         // allocated capacity
} Env;

// Constructor equivalents
Env* env_create(Env *prev);
Env* env_create_global(void);

// Methods
void env_put(Env *env, const char *id, TypeRecord *value, bool is_temp);
TypeRecord* env_get(Env *env, const char *id);
void env_print_trail(Env *env);
void env_print_table(Env *env);

// Helper to create type records
TypeRecord* type_record_create(BaseType base, int *dims, int num_dims);

// Type utility functions
const char* basetype_to_string(BaseType base);
char* type_to_string(TypeRecord *type);

// Size calculation function
size_t type_size(TypeRecord *type);

// ADDRESS HANDLING
typedef enum {
    ADDR_CONSTANT,
    ADDR_VARIABLE,
    ADDR_LABEL
} AddrType;

typedef struct {
    AddrType type;
    union {
        struct {
            enum { CONST_INT, CONST_FLOAT, CONST_BOOL } const_type;
            union {
                int int_val;
                double float_val;
                bool bool_val;
            } value;
        } constant;
        
        struct {
            char *name;
            TypeRecord *type_record;
        } variable;
        
        struct {
            char *label_name;
        } label;
    } data;
} Address;

//INTERMEDIATE CODE STUFF
// Operation codes
typedef enum {
    OP_ADD,      // Addition
    OP_SUB,      // Subtraction
    OP_MUL,      // Multiplication
    OP_DIV,      // Division
    OP_ASSIGN,   // Assignment
    OP_ARRAY_ACCESS,  // Array indexing
    OP_ADDR_CALC,     // Address calculation for arrays
    OP_LOAD,
    OP_STORE,
    OP_LEFT_SHIFT,
    OP_RIGHT_SHIFT
} OpCode;

// Instruction structure
typedef struct Instruction {
    OpCode op;
    Address *src1;
    Address *src2;
    Address *result;
    Env *env;
    struct Instruction *next;  // for linked list
} Instruction;

// Intermediate code container
typedef struct {
    Instruction *head;
    Instruction *tail;
    int instruction_count;
} IntermediateCode;

// Instruction operations
const char* opcode_to_string(OpCode op);
Instruction* instruction_create(OpCode op, Address *src1, Address *src2, Address *result, Env *env);
IntermediateCode* intermediate_code_create();
void intermediate_code_append(IntermediateCode *code, Instruction *instr);
void intermediate_code_print(IntermediateCode *code);

//address generating functions
Address* createIntAddr(int val);
Address* createFloatAddr(double val);
Address* createBoolAddr(bool val);
Address* createVarAddr(const char *name, TypeRecord *type);
Address* createLabelAddr(const char *label);
char* addr_to_string(Address *addr);

// Temp vars
char* create_temp(Env *env, BaseType base_type, int *dims, int num_dims);

// Type conversion functions
Address* widen(Env *env, Address *addr, BaseType t, BaseType w, IntermediateCode *code);
BaseType max_type(BaseType t1, BaseType t2);
BaseType get_address_type(Address *addr);

size_t get_element_width(TypeRecord *type);

//Assignment 5 Address related functions
long calculate_offset(Env *env, const char *var_name);
long calculate_base_address(Env *env);
long calculate_activation_record_size(Env *env);
long calculate_variable_size(Env *env, const char *var_name);  
void env_print_scope(Env *env);

//Assignment 6 Strength reduction and helpers:
bool is_power_of_two(int n); //check if n is power of 2
int log2_int(int n); //find multiple of 2 if so
int is_power_of_two_plus_one(int n); //check if n is 2^k + 1
int is_power_of_two_minus_one(int n); //check if n is 2^k - 1
void strength_reduction(IntermediateCode *code, Env *env);
#endif
