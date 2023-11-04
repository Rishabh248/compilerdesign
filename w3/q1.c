
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char keywords[32][10] = {"auto", "double", "int", "struct",
 "break", "else", "long","switch", "case", "enum", "register",
  "typedef", "char","extern", "return", "union", "const", "float",
  "short", "unsigned", "continue", "for", "signed", "void",
  "default", "goto", "sizeof", "voltile", "do", "if", "static",
  "while"};

struct token
{
    char token_name[10];
    unsigned int row,col;
}a;

int compare(char buffer[]){
    for(int i=0;i<32;i++){
        if(strcmp(buffer, keywords[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void relArithLogical()
{
    FILE* fp;
    fp = fopen("file1.c", "r");
    char c,buf[30];
    c = fgetc(fp);
    int colNumber=0;
    int rowNumber=1;
    while(c!=EOF)
    {
        if(c=='\n')
        {
            rowNumber++;
            colNumber=0;
            c=fgetc(fp);
            continue;
        }
        colNumber++;
        int i=0;
        buf[0]='\0';
        if(c=='=')
        {
            buf[i++]=c;
            c = fgetc(fp);

            if(c=='=')
            {
                colNumber++;
                buf[i++]=c;
                buf[i]='\0';
                strcpy(a.token_name,buf);
                a.row = rowNumber;
                a.col = colNumber;
                printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
            }
            else
            {
                buf[i]='\0';
                strcpy(a.token_name,buf);
                a.row = rowNumber;
                a.col = colNumber;
                printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
            }
        }
        else
        {
            if(c=='<'||c=='>'||c=='!')
            {
                buf[i++]=c;
                c = fgetc(fp);
                if(c=='=')
                {
                    buf[i++]=c;
                    colNumber++;
                    buf[i]='\0';
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
                buf[i]='\0';
                strcpy(a.token_name,buf);
                a.row = rowNumber;
                a.col = colNumber;
                printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
            }
            else if(c=='&')
            {
                buf[i++]=c;
                c = fgetc(fp);
                if(c=='&')
                {
                    buf[i++]=c;
                    colNumber++;
                    buf[i]='\0';
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
            }
            else if(c=='|')
            {
                buf[i++]=c;
                c = fgetc(fp);
                if(c=='|')
                {
                    buf[i++]=c;
                    colNumber++;
                    buf[i]='\0';
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
                else
                {
                    buf[i]='\0';
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
            }
            else if(c=='+' || c=='-' || c=='/' || c=='*' || c=='%')
            {
                buf[i++]=c;
                c = fgetc(fp);
                if(c=='=')
                {
                    buf[i++]=c;
                    colNumber++;
                    buf[i]='\0';
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
                else
                {
                    switch(buf[i-1])
                    {
                        case '+': if(c=='+')
                                    buf[i++]=c;
                                    break;
                        case '-': if(c=='-')
                                    buf[i++]=c;
                                    break;

                    }
                    buf[i]='\0';
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
            }
        }
        c = fgetc(fp);
    }
    fclose(fp);
}

void specKeyNumStringIde()
{
    FILE* fp;
    fp = fopen("file1.c", "r");
    char c,buf[20];
    c = fgetc(fp);
    int colNumber=0;
    int rowNumber=1;
    while(c!=EOF)
    {
        if(c=='\n')
        {
            rowNumber++;
            colNumber=0;
            c=fgetc(fp);
            continue;
        }
        colNumber++;
        int i=0;
        buf[0]='\0';
        if(c=='{' || c=='}' || c=='(' || c==')' || c=='[' || c==']' || c==';')
        {
                buf[i++]=c;
                buf[i]='\0';
                strcpy(a.token_name,buf);
                a.row = rowNumber;
                a.col = colNumber;
                printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
        }
        else if(isdigit(c)){
                while(isdigit(c)){
                    buf[i++]=c;
                    c=fgetc(fp);
                }
                colNumber++;
                buf[i]='\0';
                strcpy(a.token_name,buf);
                a.row = rowNumber;
                a.col = colNumber;
                printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                i++;
                buf[i]=c;
                continue;
            }
            else if(c=='\"'){
                buf[i++]=c;
                c=fgetc(fp);
                while(c!='\"'){
                    buf[i++]=c;
                    c=fgetc(fp);
                }
                buf[i++]=c;
                colNumber++;
                buf[i]='\0';
                strcpy(a.token_name,buf);
                a.row = rowNumber;
                a.col = colNumber;
                printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
            }
            else if(c=='\''){
                buf[i++]=c;
                c=fgetc(fp);
                while(c!='\''){
                    buf[i++]=c;
                    c=fgetc(fp);
                }
                buf[i++]='\'';
                colNumber++;
                buf[i]='\0';
                strcpy(a.token_name,buf);
                a.row = rowNumber;
                a.col = colNumber;
                printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
            }
            else if(isalpha(c) != 0)
            {
                buf[i++]=c;
                while(isalpha(c) != 0){
                    c = fgetc(fp);
                    if(isalpha(c) != 0)
                    {
                        buf[i++] = c;
                        colNumber++;
                    }
                }
                buf[i]='\0';
                if(compare(buf) == 1){
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
                else if(strcmp("main",buf)==0)
                {
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
                else{
                    while(isalpha(c)!=0 || c=='_' || isdigit(c))
                    {
                        buf[i++]=c;
                        c=fgetc(fp);
                    }
                    buf[i]='\0';
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                }
                    i++;
                    buf[i++]=c;
                    continue;
                }
                else if(c=='_')
                {
                    while(isalpha(c)!=0 || c=='_' || isdigit(c))
                    {
                        buf[i++]=c;
                        c=fgetc(fp);
                    }
                    buf[i]='\0';
                    strcpy(a.token_name,buf);
                    a.row = rowNumber;
                    a.col = colNumber;
                    printf("\n <%s,%d,%d>",a.token_name,a.row,a.col);
                    buf[++i]=c;
                    continue;
                }
            c = fgetc(fp);
        }
     fclose(fp);
}

void getNextToken()
{
    printf("The tokens generated for special symbols, keywords, numerical constants, string literals and identifiers are: ");
    specKeyNumStringIde();
    printf("\n\nThe tokens generated for relational, arithmetic and logical operators are: ");
    relArithLogical();
}

int main()
{
    FILE *fp1,*fptr2;
    fp1 = fopen("file.c", "r");
    if(fp1==NULL)
    {
        printf("File does not exist");
        exit(0);
    }
    fptr2 = fopen("file1.c","w+");
    char ch = fgetc(fp1);
    int c = 0;
    while(ch != EOF)
    {
        if(ch == '"')
        {
            if(c == 1)
            {
                fputc(ch, fptr2);
                c = 0;
                ch = fgetc(fp1);
            }
            else
            {
                fputc(ch, fptr2);
                c = 1;
                ch = fgetc(fp1);
            }
        }
        if(ch == '#')
        {
            while(ch != '\n')
                ch = fgetc(fp1);
        }
        else
            fputc(ch, fptr2);
        ch = fgetc(fp1);
    }
    fclose(fptr2);
    getNextToken();
    fclose(fp1);
}
