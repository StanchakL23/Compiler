%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

enum { //token types/codes for parser
    BASIC = 256, ID, NUM, REAL, BOOLCONST,
    WHILE_, IF_, ELSE_, RETURN_, BREAK_, DO,
    LEFTBRACE, RIGHTBRACE, SEMIC, EQUALS, PLUS,
    MINUS, LEFTPARAN, RIGHTPARAN, LT, GT, LE, GE,
    LEFTBRACK, RIGHTBRACK, AND, OR, NE, ASSIGN, NOT
};

typedef union {  //yylval object types for Bison use
    int intVal;
    double dVal;
    char *strVal;
    bool bVal;

} YYSTYPE;
YYSTYPE yylval;

// symbol table (implemented temporarily as a list)
//My assignment 1 is in Java, and i will 
//convert to C before assignment 3 for scope implementation
#define MAX_SYMBOLS 500
char * symbols[MAX_SYMBOLS];
int symbol_count = 0;
extern FILE *yyin;

void insertSymbol(const char *s) {
    //Check to make sure the symbol doesn't already exist
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbols[i], s) == 0) return;
    }
    symbols[symbol_count++] = strdup(s);
}

int yywrap( void ) {
    return 1;
}

%}

delim       [ \t\n\r]
ws          {delim}+
letter      [A-Za-z]
digit       [0-9]
id          {letter}({letter}|{digit})*
basic       (int)|(float)|(bool)
num         {digit}+
real        {digit}+"."{digit}*

%%
{ws}        { /* ignore whitespace */ }

"true"      { yylval.bVal = true; printf("true "); return BOOLCONST; }
"false"     { yylval.bVal = false; printf("false "); return BOOLCONST; }

"while"     { printf("while "); return WHILE_; }
"if"        { printf("if "); return IF_; }
"else"      { printf("else "); return ELSE_; }
"return"    { printf("return "); return RETURN_; }
"break"     { printf("break "); return BREAK_; }
"do"        { printf("do "); return DO; }

"{"         { printf("{ "); return LEFTBRACE; }
"}"         { printf("} "); return RIGHTBRACE; }
";"         { printf("; "); return SEMIC; }
"<="        { printf("<= "); return LE; }
">="        { printf(">= "); return GE; }
"<"         { printf("< "); return LT; }
">"         { printf("> "); return GT; }
"=="        { printf("== "); return EQUALS; }
"="         { printf("= "); return ASSIGN; }
"+"         { printf("+ "); return PLUS; }
"-"         { printf("- "); return MINUS; }
"("         { printf("( "); return LEFTPARAN; }
")"         { printf(") "); return RIGHTPARAN; }
"["         { printf("[ "); return LEFTBRACK; }
"]"         { printf("] "); return RIGHTBRACK; }
"&&"        { printf("&& "); return AND; }
"||"        { printf("|| "); return OR; }
"!="         { printf("!= "); return NE; }
"!"         { printf("! "); return NOT; }

{basic}     { yylval.strVal = strdup(yytext); printf("basic "); return BASIC; }

{real}      { yylval.dVal = atof(yytext); printf("real "); return REAL; }
{num}       { yylval.intVal = atoi(yytext); printf("num "); return NUM; }

{id}        { insertSymbol(yytext); yylval.strVal = strdup(yytext); printf("id "); return ID; }
%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Could not open file");
            return 1;
        }
        yyin = file;
    }

    int token;
    while ((token = yylex()) != 0) {
        // token processing is done in yylex
    }

    printf("\n\nParsing completed successfully.\n\n");
    
    // print symbol table
    printf("Symbol Table: \n");
    printf("----\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("ID: %s\n", symbols[i]);
    }
    printf("----\n");
    return 0;
}