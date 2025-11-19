%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.tab.h" //include token definitions from Bison

// Temporary symbol table implemented in parser
extern FILE *yyin;

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

"true"      { yylval.bVal = true; return BOOLCONST; }
"false"     { yylval.bVal = false; return BOOLCONST; }

"while"     { return WHILE_; }
"if"        { return IF_; }
"else"      { return ELSE_; }
"return"    { return RETURN_; }
"break"     { return BREAK_; }
"do"        { return DO; }

"{"         { return LEFTBRACE; }
"}"         { return RIGHTBRACE; }
";"         { return SEMIC; }
"<="        { return LE; }
">="        { return GE; }
"<"         { return LT; }
">"         { return GT; }
"=="        { return EQUALS; }
"="         { return ASSIGN; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"("         { return LEFTPARAN; }
")"         { return RIGHTPARAN; }
"["         { return LEFTBRACK; }
"]"         { return RIGHTBRACK; }
"&&"        { return AND; }
"||"        { return OR; }
"!="        { return NE; }
"!"         { return NOT; }
"*"         { return MULTIPLY; }
"/"         { return DIVIDE; }

{basic}     { printf("LEX: BASIC(%s)\n", yytext); fflush(stdout); yylval.str = strdup(yytext); return BASIC; }

{real}      { yylval.real = atof(yytext); return REAL; }
{num}       { yylval.num = atoi(yytext); return NUM; }

{id}        { printf("LEX: ID(%s)\n", yytext); fflush(stdout); yylval.str = strdup(yytext); return ID; }
%%

/*int main(int argc, char **argv) {
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
}*/