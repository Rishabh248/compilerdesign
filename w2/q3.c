#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {"printf", "int", "float", "return", "break", "continue", "if", "else", "for", "while","scanf","return","case","else-if",};


void stringUpper(char *str,const int n){
    for(int i = 0;i<n;i++)
        str[i] = toupper(str[i]);
}


int isKeyword(const char* str){
    for(int i = 0;i<sizeof(keywords)/sizeof(char*);i++){
        if(strncmp(str,keywords[i],strlen(keywords[i])) == 0)
            return 1;
    }
    return 0;
}





int main(){
    char buff[2048];

    FILE *fa;

    char fname[100],c;

    printf("Enter file name\n");
    scanf("%s",fname);
    fa = fopen(fname,"r");

    if(!fa){
        printf("cannot open file\n");
        exit(0);
    }




    int line =1,col=1,j=0;




    printf("Keywords are:\n");

    while((c = fgetc(fa)) != EOF){
        if(isalpha(c)){
            buff[j++] = c;
        }
        else{
            buff[j] = '\0';
            if(isKeyword(buff)){
                stringUpper(buff,j);
                printf("%s: at(line %d, col %d)\n",buff,line,col-j);
            }
            j = 0;
        }
        if(c == '\n'){
            line++;
            col = 1;
        }
        else col++;
    }
    fclose(fa);
    return 0;
}