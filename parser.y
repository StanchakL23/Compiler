%{
/* ------------------- C Declarations ------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Temporary symbol table as a list */
#define MAX_SYMBOLS 100
char *symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

/* Helper function to add identifiers to symbol table */
void add_symbol(const char *sym) {
    if (symbol_count < MAX_SYMBOLS) {
        symbol_table[symbol_count++] = strdup(sym);
    }
}

/* Error handling function */
void yyerror(const char *s);
int yylex(void);
%}

// TOKEN DECLARATION
%token BASIC ID NUM REAL BOOLCONST WHILE_ IF_ ELSE_ RETURN_ BREAK_ DO
%token LEFTBRACE RIGHTBRACE SEMIC EQUALS PLUS MINUS LEFTPARAN RIGHTPARAN 
%token LT GT LE GE LEFTBRACK RIGHTBRACK AND OR NE ASSIGN NOT MULTIPLY DIVIDE

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
    : decls decl
        { printf("decls -> decls decl\n"); }
    | /* empty */
        { printf("decls -> e\n"); }
    ;

decl
    : type ID SEMIC
        { printf("decl -> type ID SEMIC\n"); add_symbol($2); }
    ;

type
    : type '[' NUM ']'
        { printf("type -> type '[' NUM ']'\n"); }
    | BASIC
        { printf("type -> BASIC\n"); }
    ;

stmts
    : stmts stmt
        { printf("stmts -> stmts stmt\n"); }
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

/*program
    : stmt_list
        { printf("program -> stmt_list\n"); }
    ;

stmt_list
    : stmt_list stmt
        { printf("stmt_list -> stmt_list stmt\n"); }
    | stmt
        { printf("stmt_list -> stmt\n"); }
    ;

stmt
    : loc ASSIGN expr SEMI
        { printf("stmt -> loc ASSIGN expr SEMI\n"); }
    | IF expr THEN stmt
        { printf("stmt -> IF expr THEN stmt\n"); }
    | WHILE expr DO stmt
        { printf("stmt -> WHILE expr DO stmt\n"); }
    | BEGIN stmt_list END
        { printf("stmt -> BEGIN stmt_list END\n"); }
    | error SEMI
        {
            printf("Error recovered at statement boundary.\n");
            yyerrok; 
        }
    ;

loc
    : ID
        {
            printf("loc -> ID\n");
            add_symbol(yytext); 
        }
    ;

expr
    : expr ADDOP expr
        { printf("expr -> expr ADDOP expr\n"); }
    | expr MULOP expr
        { printf("expr -> expr MULOP expr\n"); }
    | LPAREN expr RPAREN
        { printf("expr -> LPAREN expr RPAREN\n"); }
    | NUM
        { printf("expr -> NUM\n"); }
    | loc
        { printf("expr -> loc\n"); }
    ;
*/
%%

/* ------------------- Supporting C Code ------------------- */
void yyerror(const char *s) {
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
