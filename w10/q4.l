%{
	int rd = 0;
	int wr = 0;
%}

%%
scanf { rd++; fwrite("read", 1, 4, yyout); }
printf { wr++; fwrite("write", 1, 5, yyout); }
%%

main(int argc, char **argv) {
	yyin = fopen("inp4.txt", "r");
	yyout = fopen("out4.txt", "w+");
	yylex();
	printf("rd:%d wr:%d\n", rd, wr); 
}
int yywrap() {
	return 1;
}