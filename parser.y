%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "symbtab.h"

//current environment pointer (for scope)
Env *current_env = NULL;
IntermediateCode *global_code = NULL;

// Temporary storage for building type records during parsing
static BaseType current_base_type;
static int dimension_stack[10];  // fixed size for simplicity
static int dimension_count = 0;

extern FILE *yyin;
//Declaration for error handling
void yyerror(const char *s);
int yylex(void);
%}

%code requires {
    #include "symbtab.h"
}

%union {
    char *str;
    int num;
    float real;
    bool bVal;
    Address *addr;
}

// TOKEN DECLARATION
%token WHILE_ IF_ ELSE_ RETURN_ BREAK_ DO
%token LEFTBRACE RIGHTBRACE SEMIC EQUALS PLUS MINUS LEFTPARAN RIGHTPARAN 
%token LT GT LE GE LEFTBRACK RIGHTBRACK AND OR NE ASSIGN NOT MULTIPLY DIVIDE
%token <str> ID BASIC
%token <num> NUM
%token <real> REAL
%token <bVal> BOOLCONST
%type <addr> loc bool join equality rel expr term unary factor

%start program

// GRAMMAR RULES
%%
program
    : LEFTBRACE decls stmts RIGHTBRACE
        { 
            printf("program -> { decls stmts }\n"); 
        }
    ;

block
    : LEFTBRACE { current_env = env_create(current_env); } decls stmts RIGHTBRACE
        { 
            printf("block -> decls stmts\n");
            env_print_scope(current_env);
            current_env = current_env->prev; 
        }
    ;

decls
    : /* empty */
        { printf("decls -> e\n"); }
    | decls decl
        { printf("decls -> decl decls\n"); }
    ;

decl
    : base_type_spec dims ID SEMIC
        {
            printf("decl -> base_type_spec dims ID SEMIC\n");  
            TypeRecord *type = type_record_create(current_base_type, dimension_stack, dimension_count);
            env_put(current_env, $3, type, false);
            dimension_count = 0;
            free($3);
        }
    ;

base_type_spec
    : BASIC
        {
            dimension_count = 0;  // reset dimensions
            if (strcmp($1, "int") == 0) current_base_type = INT;
            else if (strcmp($1, "float") == 0) current_base_type = FLOAT;
            else if (strcmp($1, "bool") == 0) current_base_type = BOOL;
            free($1);
        }

dims    //new rule for array dimension tracking
    : dims LEFTBRACK NUM RIGHTBRACK
        {
            printf("dims -> dims [ NUM ]\n");
            dimension_stack[dimension_count++] = $3;
        }
    | /* empty */
        { printf("dims -> e\n"); }
    ;

stmts
    : stmt stmts
        { printf("stmts -> stmt stmts\n"); }
    | /* empty */
        { printf("stmts -> e\n"); }
    ;

stmt
    : loc ASSIGN bool SEMIC
        { 
            printf("stmt -> loc = bool ;\n"); 
            
            Address *destination_addr = $1; 
            Address *source_addr = $3;      
            OpCode op;
            
            // Check if destination is a temporary variable (like t12)
            // If it's a temporary, it means it holds the calculated address of an array element.
            if (destination_addr && destination_addr->type == ADDR_VARIABLE && destination_addr->data.variable.name[0] == 't') {
                op = OP_STORE; // Use STORE for array element assignment: STORE $3 into address $1
            } else {
                op = OP_ASSIGN; // Use ASSIGN for simple variable assignment: $1 = $3
            }
            
            // Note: src2 is NULL for both
            Instruction *instr = instruction_create(op, source_addr, NULL, destination_addr, current_env);
            intermediate_code_append(global_code, instr);
        }
    | IF_ LEFTPARAN bool RIGHTPARAN stmt
        { printf("stmt -> if ( bool ) stmt\n"); }
    | IF_ LEFTPARAN bool RIGHTPARAN stmt ELSE_ stmt
        { printf("stmt -> if ( bool ) stmt else stmt\n"); }
    | WHILE_ LEFTPARAN bool RIGHTPARAN stmt
        { printf("stmt -> while ( bool ) stmt\n"); }
    | DO stmt WHILE_ LEFTPARAN bool RIGHTPARAN SEMIC
        { printf("stmt -> do stmt while ( bool ) ;\n"); }
    | BREAK_ SEMIC
        { printf("stmt -> break ;\n"); }
    | RETURN_ bool SEMIC
        { printf("stmt -> return bool ;\n"); }
    | block
        { printf("stmt -> block\n"); }
    | error SEMIC
        { printf("Recovered from a bad statement (missing ';').\n"); yyerrok; }
    | error RIGHTBRACE
        { printf("Recovered from a bad block (found the closing '}' for this block).\n"); yyerrok; }
    ;

loc
    : loc LEFTBRACK bool RIGHTBRACK
        {
            printf("loc -> loc [ bool ]\n");

            Address *base_addr = $1;
            Address *index_addr = $3;
            
            // --- ERROR CHECKING ---
            if (!base_addr || base_addr->type != ADDR_VARIABLE || !base_addr->data.variable.type_record) {
                 fprintf(stderr, "Error: Cannot index non-variable or undeclared array.\n");
                 $$ = NULL;
            } else {
                // Address is valid, proceed with array access calculation
                TypeRecord *array_type = base_addr->data.variable.type_record;
                
                size_t element_width = get_element_width(array_type); 
                
                char *temp_offset_name = create_temp(current_env, INT, NULL, 0); 
                TypeRecord *temp_offset_type = env_get(current_env, temp_offset_name);
                Address *temp_offset_addr = createVarAddr(temp_offset_name, temp_offset_type);

                Address *width_addr = createIntAddr(element_width); 

                Instruction *mul_instr = instruction_create(OP_MUL, index_addr, width_addr, temp_offset_addr, current_env);
                intermediate_code_append(global_code, mul_instr);
                
                BaseType result_basetype = array_type->base_type;
                
                char *temp_final_name = create_temp(current_env, result_basetype, NULL, 0);
                TypeRecord *temp_final_type = env_get(current_env, temp_final_name);
                Address *temp_final_addr = createVarAddr(temp_final_name, temp_final_type);

                Instruction *add_instr = instruction_create(OP_ADD, base_addr, temp_offset_addr, temp_final_addr, current_env);
                intermediate_code_append(global_code, add_instr);
                
                $$ = temp_final_addr;
            }
        }
    | ID
    { 
        printf("loc -> ID\n");
        TypeRecord *type = env_get(current_env, $1);
        if (!type) {
            fprintf(stderr, "Error: Undeclared identifier '%s'\n", $1);
            $$ = NULL; 
        } else {
            $$ = createVarAddr($1, type);
        }
        free($1); 
    }
    ;

bool
    : bool OR join
        { printf("bool -> bool || join\n"); }
    | join
        { printf("bool -> join\n"); }
    ;

join
    : join AND equality
        { printf("join -> join && equality\n"); }
    | equality
        { printf("join -> equality\n"); }
    ;

equality
    : equality EQUALS rel
        { printf("equality -> equality == rel\n"); }
    | equality NE rel
        { printf("equality -> equality != rel\n"); }
    | rel
        { printf("equality -> rel\n"); }
    ;

rel
    : expr LT expr
        { printf("rel -> expr < expr\n"); }
    | expr LE expr
        { printf("rel -> expr <= expr\n"); }
    | expr GT expr
        { printf("rel -> expr > expr\n"); }
    | expr GE expr
        { printf("rel -> expr >= expr\n"); }
    | expr
        { printf("rel -> expr\n"); }
    ;

expr
    : expr PLUS term
        { 
            printf("expr -> expr + term\n"); 
            BaseType t1 = get_address_type($1);
            BaseType t2 = get_address_type($3);

            BaseType max_t = max_type(t1, t2);
            Address *src1 = widen(current_env, $1, t1, max_t, global_code);
            Address *src2 = widen(current_env, $3, t2, max_t, global_code);

            char *temp_name = create_temp(current_env, max_t, NULL, 0);
            TypeRecord *temp_type = env_get(current_env, temp_name);
            Address *result = createVarAddr(temp_name, temp_type);

            Instruction *instr = instruction_create(OP_ADD, src1, src2, result, current_env);
            intermediate_code_append(global_code, instr);

            $$ = result;
        }
    | expr MINUS term
        { 
            printf("expr -> expr - term\n"); 
            BaseType t1 = get_address_type($1);
            BaseType t2 = get_address_type($3);

            BaseType max_t = max_type(t1, t2);
            Address *src1 = widen(current_env, $1, t1, max_t, global_code);
            Address *src2 = widen(current_env, $3, t2, max_t, global_code);

            char *temp_name = create_temp(current_env, max_t, NULL, 0);
            TypeRecord *temp_type = env_get(current_env, temp_name);
            Address *result = createVarAddr(temp_name, temp_type);

            Instruction *instr = instruction_create(OP_SUB, src1, src2, result, current_env);
            intermediate_code_append(global_code, instr);

            $$ = result;
        }
    | term
        { 
            printf("expr -> term\n"); 
            $$ = $1;
        }
    ;

term
    : term MULTIPLY unary
        { 
            printf("term -> term * unary\n"); 
            BaseType t1 = get_address_type($1);
            BaseType t2 = get_address_type($3);

            BaseType max_t = max_type(t1, t2);
            Address *src1 = widen(current_env, $1, t1, max_t, global_code);
            Address *src2 = widen(current_env, $3, t2, max_t, global_code);

            char *temp_name = create_temp(current_env, max_t, NULL, 0);
            TypeRecord *temp_type = env_get(current_env, temp_name);
            Address *result = createVarAddr(temp_name, temp_type);

            Instruction *instr = instruction_create(OP_MUL, src1, src2, result, current_env);
            intermediate_code_append(global_code, instr);

            $$ = result;
        }
    | term DIVIDE unary
        { 
            printf("term -> term / unary\n"); 
            BaseType t1 = get_address_type($1);
            BaseType t2 = get_address_type($3);

            BaseType max_t = max_type(t1, t2);
            Address *src1 = widen(current_env, $1, t1, max_t, global_code);
            Address *src2 = widen(current_env, $3, t2, max_t, global_code);

            char *temp_name = create_temp(current_env, max_t, NULL, 0);
            TypeRecord *temp_type = env_get(current_env, temp_name);
            Address *result = createVarAddr(temp_name, temp_type);

            Instruction *instr = instruction_create(OP_DIV, src1, src2, result, current_env);
            intermediate_code_append(global_code, instr);

            $$ = result;
        }
    | unary
        { 
            printf("term -> unary\n"); 
            $$ = $1;
        }
    ;

unary
    : NOT unary
        { printf("unary -> ! unary\n"); }
    | MINUS unary
        { printf("unary -> - unary\n"); }
    | factor
        { printf("unary -> factor\n"); }
    ;

factor
    : LEFTPARAN bool RIGHTPARAN
        { 
            printf("factor -> ( bool )\n");
            $$ = $2;
        }
    | loc
        { 
            printf("factor -> loc\n"); 
            Address *loc_addr = $1;
            
            // Check if loc is a temporary address (an array element address)
            if (loc_addr && loc_addr->type == ADDR_VARIABLE && loc_addr->data.variable.name[0] == 't') {
                BaseType result_basetype = get_address_type(loc_addr);
                char *temp_load_name = create_temp(current_env, result_basetype, NULL, 0);
                TypeRecord *temp_load_type = env_get(current_env, temp_load_name);
                Address *temp_load_addr = createVarAddr(temp_load_name, temp_load_type);
                
                Instruction *instr = instruction_create(OP_LOAD, loc_addr, NULL, temp_load_addr, current_env);
                intermediate_code_append(global_code, instr);
                
                $$ = temp_load_addr; // Return the address of the loaded value
            } else {
                // It's a simple variable (i, j, v, x), just return its address
                $$ = loc_addr;
            }
        }
    | NUM
        { 
            printf("factor -> NUM\n"); 
            $$ = createIntAddr($1);
        }
    | REAL
        { 
            printf("factor -> REAL\n"); 
            $$ = createFloatAddr($1);
        }
    | BOOLCONST
        { printf("factor -> BOOLCONST\n"); }
    ;

%%

void yyerror(const char *s) { //Completely stops parsing if error is not recoverable.
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main(int argc, char *argv[]) {
    printf("Starting parse...\n");

    if (argc != 2) {
            fprintf(stderr, "Usage: %s <input_file_path>\n", argv[0]);
            exit(1); 
        }

    // Open the specified file for reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        exit(1);
    }

    yyin = input_file;
    current_env = env_create_global();
    global_code = intermediate_code_create();
    int result = yyparse();

    if (result != 0) {
        printf("Unrecoverable syntax error encountered. Parsing terminated.\n");
        return 1;
    }

    printf("\nParsing complete.\n");
    printf("Applying strength reduction:\n");
    strength_reduction(global_code, current_env);
    printf("Strength reduction complete.\n");
    printf("\nFinal symbol table:\n");
    env_print_table(current_env);
    intermediate_code_print(global_code);
    fclose(input_file);
    return 0;
}
