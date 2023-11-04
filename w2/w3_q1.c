#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "q1.c"
#include "q2.c"

#define FILEINPUT "input.c"



struct token
{
    char lexeme[64];
    int row, col;
    char type[20];
};





static int row = 1, col = 1;

const char specialsymbols[] = {'?', ';', ':', ','};
const char *keywords[] = {"const", "char", "int", "return", "for", "while", "do",
                          "switch", "if", "else", "unsigned", "case", "break"};

const char arithmeticsymbols[] = {'*'};


int charBelongsTo(int c, const char *arr, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (c == arr[i])
        {
            return 1;
        }
    }
    return 0;
}

int isArithmeticRelationalLogical(char c)
{
    return charBelongsTo(c, arithmeticsymbols, sizeof(arithmeticsymbols) / sizeof(char)) ||
           c == '<' || c == '>' || c == '!' || c == '&' || c == '|';
}

int isSpecialSymbolKeywordNumConstantStringLiteralIdentifier(char c)
{
    return charBelongsTo(c, specialsymbols, sizeof(specialsymbols) / sizeof(char)) ||
           isKeyword(c) || isNumConstant(c) || isStringLiteral(c) || isIdentifier(c);
}





void fillToken(struct token *tkn, char c, int row, int col, const char *type)
{
    tkn->row = row;
    tkn->col = col;
    strcpy(tkn->type, type);
    tkn->lexeme[0] = c;
    tkn->lexeme[1] = '\0';
}

struct token getNextToken(FILE *f1)
{
    int c;
    struct token tkn = {.row = -1};

    int gotToken = 0;

    while (!gotToken && (c = fgetc(f1)) != EOF)
    {
        if (c == '/')
        {
            int nextChar = fgetc(f1);
            if (nextChar == '/' || nextChar == '*')
            {
                ungetc(nextChar, f1);
                skipComments(f1);
                continue;
            }
            else
            {
                fseek(f1, -1, SEEK_CUR);
            }
        }
        else if (c == '#')
        {
            skipPreprocessorDirectives(f1);
            continue;
        }

        if (isArithmeticRelationalLogical(c))
        {
            // ...
            printf("Found ARITHMETIC/RELATIONAL/LOGICAL OPERATOR: %c\n", c);
        }
        else if (isSpecialSymbolKeywordNumConstantStringLiteralIdentifier(c))
        {
            if (isSpecialSymbol(c))
            {
                // ...
                printf("Found SPECIAL SYMBOL: %c\n", c);
            }
            else if (isKeyword(c))
            {
                // ...
                printf("Found KEYWORD: %s\n", c);
            }
            else if (isNumConstant(c))
            {
                // ...
                printf("Found NUMERIC CONSTANT: %c\n", c);
            }
            else if (isStringLiteral(c))
            {
                // ...
                printf("Found STRING LITERAL: %c\n", c);
            }
            else if (isIdentifier(c))
            {
                // ...
                printf("Found IDENTIFIER: %c\n", c);
            }
        }
        // ... (rest of the code remains the same)
    }

    return tkn;
}

int main()
{
    FILE *f1 = fopen(FILEINPUT, "r");
    if (f1 == NULL)
    {
        printf("Error! File cannot be opened!\n");
        return 0;
    }

    struct token tkn;
    while ((tkn = getNextToken(f1)).row != -1)
    {
        printf("<%s, %d, %d>\n", tkn.type, tkn.row, tkn.col);
    }

    fclose(f1);

    return 0;
}
