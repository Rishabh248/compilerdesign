%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}

%token NUM N EOL
%left '+' '-'
%left '*' '/'
%right '^'

%%
input: /* empty */
      | input line
      ;

line: EOL
    | exp EOL { printf("Result: %d\n", $1); }
    ;

exp: NUM
   | exp exp '+' { $$ = $1 + $2; }
   | exp exp '-' { $$ = $1 - $2; }
   | exp exp '*' { $$ = $1 * $2; }
   | exp exp '/' { $$ = $1 / $2; }
   | exp exp '^' { int result = 1;
                  for (int i = 0; i < $2; i++) {
                      result *= $1;
                  }
                  $$ = result;
                }
   | exp N
   ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}
