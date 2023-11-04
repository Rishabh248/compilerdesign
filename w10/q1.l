%{
	#include <stdio.h>
	int vowels = 0;
	int consonants = 0;
%}



%%
[a,e,i,o,u,A,E,I,O,U] {vowels++;}
[a-zA-Z] {consonants++;}
%%


int main(int argc,char**argv) {
	yylex();
	printf("vowels: %d constonants : %d", vowels, consonants);
}

int yywrap() { 
	return 1;
}