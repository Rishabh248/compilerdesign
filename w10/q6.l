%{
	#include <stdio.h>
    #include <ctype.h>
%}

%%
\/\/.* { fwrite(yytext, 1, yyleng, yyout); }
\/\*(.|\n)*\*\/ { fwrite(yytext, 1, yyleng, yyout); }
[A-Z] { yytext[0] += 32; fwrite(yytext, 1, yyleng, yyout); }
%%

main(int argc, char **argv) {
	yyin = fopen("inp6.txt", "r");
	yyout = fopen("out6.txt", "w+");
	yylex();
}

int yywrap() {
	return 1;
}