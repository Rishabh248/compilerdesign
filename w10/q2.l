




%{
	int chars = 0;
	int words = 0;
	int blanks = 0;
	int lines = 0;
%}


%%
" " {blanks++;}
[a-zA-Z]+ { words++; chars += strlen(yytext); }
\n { chars++; lines++; }
. { chars++; }
%%


int main(int argc, char **argv) {
	yyin = fopen("inp2.txt", "r");
	yylex();
	printf("lines:%d words:%d chars:%d blanks:%d\n", lines, words, chars, blanks); 
}
int yywrap() {
	return 1;
}