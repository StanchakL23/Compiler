%{
/* ------------------- C Declarations ------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Temporary symbol table as a list */
#define MAX_SYMBOLS 100
char *symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

/* Helper function to add identifiers to symbol table */
void add_symbol(const char *sym) {
    if (symbol_count < MAX_SYMBOLS) {
        for ( int i = 0, found = 0; i < symbol_count; i++) {
            if (strcmp(symbol_table[i], sym) == 0) {return;}
        }
        symbol_table[symbol_count++] = strdup(sym);
    }
}

/* Error handling function */
void yyerror(const char *s);
int yylex(void);
%}

%union {
    char *str;
    int num;
    float real;
    bool bVal;
}

// TOKEN DECLARATION
%token WHILE_ IF_ ELSE_ RETURN_ BREAK_ DO
%token LEFTBRACE RIGHTBRACE SEMIC EQUALS PLUS MINUS LEFTPARAN RIGHTPARAN 
%token LT GT LE GE LEFTBRACK RIGHTBRACK AND OR NE ASSIGN NOT MULTIPLY DIVIDE
%token <str> ID BASIC
%token <num> NUM
%token <real> REAL
%token <bVal> BOOLCONST

%start program

// GRAMMAR RULES
%%
program
    : block
        { printf("program -> block\n"); }
    ;

block
    : LEFTBRACE decls stmts RIGHTBRACE
        { printf("block -> decls stmts\n"); }
    ;

decls
    : decl decls
        { printf("decls -> decl decls\n"); }
    | /* empty */
        { printf("decls -> e\n"); }
    ;

decl
    : type ID SEMIC
        { printf("decl -> type ID SEMIC\n"); add_symbol($2); }
    ;

type
    : BASIC type1
        { printf("type -> BASIC type1\n"); }
    ;

type1
    : type1 LEFTBRACK NUM RIGHTBRACK
        { printf("type1 -> type1 [ NUM ]\n"); }
    | /* empty */
        { printf("type1 -> e\n"); }
    ;

stmts
    : stmt stmts
        { printf("stmts -> stmt stmts\n"); }
    | /* empty */
        { printf("stmts -> e\n"); }
    ;

stmt
    : loc ASSIGN bool SEMIC
        { printf("stmt -> loc = bool ;\n"); }
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
    | block
        { printf("stmt -> block\n"); }
    | error SEMIC
        { printf("Recovered from a bad statement (missing ';').\n"); yyerrok; }
    | error RIGHTBRACE
        { printf("Recovered from a bad block (found the closing '}' for this block).\n"); yyerrok; }
    ;

loc
    : loc LEFTBRACK bool RIGHTBRACK
        { printf("loc -> loc [ bool ]\n"); }
    | ID
        { printf("loc -> ID\n"); add_symbol($1); }
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
        { printf("expr -> expr + term\n"); }
    | expr MINUS term
        { printf("expr -> expr - term\n"); }
    | term
        { printf("expr -> term\n"); }
    ;

term
    : term MULTIPLY unary
        { printf("term -> term * unary\n"); }
    | term DIVIDE unary
        { printf("term -> term / unary\n"); }
    | unary
        { printf("term -> unary\n"); }
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
        { printf("factor -> ( bool )\n"); }
    | loc
        { printf("factor -> loc\n"); }
    | NUM
        { printf("factor -> NUM\n"); }
    | REAL
        { printf("factor -> REAL\n"); }
    | BOOLCONST
        { printf("factor -> BOOLCONST\n"); }
    ;

%%

void yyerror(const char *s) { //Completely stops parsing if error is not recoverable.
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main(void) {
    printf("Starting parse...\n");
    yyparse();

    printf("\nParsing complete.\nSymbol table:\n");
    for (int i = 0; i < symbol_count; i++)
        printf("  %s\n", symbol_table[i]);
    return 0;
}
