%{
#include <math.h>
%}

DIGIT [0-9]
IDENTIFIER [a-z]*
KEYWORD void|int
SEPARATOR_SYMBOL ";"|","
SYMBOL "("|")"|"{"|"}"
ASSIGNMENT_OPERATOR "="
EQUALITY_OPERATOR "=="
OPERATOR "+"|"-"|"*"|"/"

%%
[ \t\n]+    /* skip whitespaces */
{KEYWORD}   printf("A keyword: %s \n", yytext);
{DIGIT}+    printf("An integer: %s (%d)\n", yytext, atoi(yytext));
{IDENTIFIER}    printf("An identifier: %s \n", yytext);
{SYMBOL}    printf("A symbol: %s \n", yytext);
{SEPARATOR_SYMBOL}    printf("A separator symbol: %s \n", yytext);
{OPERATOR}    printf("An operator: %s \n", yytext);
{ASSIGNMENT_OPERATOR}    printf("An assignment operator: %s \n", yytext);
{EQUALITY_OPERATOR}    printf("An equality operator: %s \n", yytext);
.   printf( "Unrecognized character: %s\n", yytext );
%%


int yywrap()
{
  return 1;
}


int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if(fp)
			yyin = fp;
	}
	yylex();
	return 1;
}