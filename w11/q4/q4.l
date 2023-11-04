
%{
#include "q4.tab.h"
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUM; }
"n"         { return N; }
[-+*/^]     { return yytext[0]; }
\n          { return EOL; }
[ \t]       { /* ignore whitespace */ }
.           { /* ignore other characters */ }
%%

int yywrap() {
    return 1;
}

