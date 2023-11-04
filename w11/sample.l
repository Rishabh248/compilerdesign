%{
#include "sample.tab.h"
//filename.tab.h : here both flex and bison
%}
%%
[0-9]+ {return NUMBER; }
\n {return NL ;}
[a-zA-Z][a-zA-Z0-9_]* {return ID; }
. {return yytext[0]; }
%%
int yywrap(){
	return 1;
	
}