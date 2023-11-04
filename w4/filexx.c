
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 20


typedef enum {
    IDENTIFIER,
    KEYWORD,
    STRING_LITERAL,
    NUMERIC_CONSTANT,
    OPERATOR,
    BRACKET,
    SPECIAL_SYMBOL,
    RELATIONAL_OPERATOR,
    CHARACTER_CONSTANT
} TYPE;



typedef struct symbolLinkedList {
    Symbol *head;
} SymbolLinkedList;

SymbolLinkedList st[MAX_SIZE];




int removeSpaces(){
    FILE *fa, *fb;
    int ca, cb;
    fa = fopen("input.c", "r");
    if(fa == NULL){
        printf("Cannot open file!\n");
        exit(0);
    }
    fb = fopen("output1.c", "w");
    ca = getc(fa);
    while(ca != EOF){
        if(ca == ' ' || ca == '\t'){
            putc(' ',fb);
            while(ca == ' ' || ca == '\t')
                ca = getc(fa);
        }
        if(ca == '/'){
            cb = getc(fa);
            if(cb == '/'){
                while(ca != '\n')
                    ca = getc(fa);
            }
            else if(cb == '*'){
                do{
                    while(ca != '*')
                        ca = getc(fa);
                    ca = getc(fa);
                }while(ca != '/');
            }
            else{
                putc(ca, fb);
                putc(cb, fb);
            }
        }
        else
            putc(ca, fb);
        ca = getc(fa);
    }
    fclose(fa);
    fclose(fb);
    return 0;
}



int preProcessIgnore(){
    FILE *fin = fopen("output1.c", "r");
    char c = 0;
    char buffer[100];
    buffer[0] = '\0';
    int i = 0;
    char *includeStr = "include", *defineStr = "define", *mainStr = "main";
    int mainFlag = 0, rowNum = 1;
    while(c != EOF){
        c = fgetc(fin);
        if(c == '#' && mainFlag == 0){
            c = 'a';
            while(isalpha(c) != 0){
                c = fgetc(fin);
                buffer[i++] = c;
            }
            buffer[i] = '\0';
            if(strstr(buffer, includeStr) != NULL || strstr(buffer, defineStr) != NULL){
                rowNum++;
                while(c!='\n'){
                    c = fgetc(fin);
                }
            }
            else{
                for(int j=0;j<i;j++);
                while(c!='\n'){
                    c = fgetc(fin);
                }
            }
            i = 0;
            buffer[0]= '\0';
        }
        else{
            if(mainFlag == 0){
                buffer[i++] = c;
                buffer[i] = '\0';
                if(strstr(buffer, mainStr) != NULL){
                    mainFlag = 1;
                }
            }
            if(c == ' ' || c == '\n'){
                buffer[0] = '\0';
                i = 0;
            }
        }
    }
    fclose(fin);
    return rowNum;
}



char keywords[32][10] = {"auto", "double", "int", "struct",
"break", "else", "long", "switch", "case", "enum", "register",
"typedef", "char", "extern", "return", "union", "const", "float",
"short", "unsigned", "continue", "for", "signed", "void",
"default", "goto", "sizeof", "voltile", "do", "if", "static",
"while"}; 



char operators[5] = {'+','-','/','%','*'};
char brackets[6] = {'(', ')', '[', ']', '{', '}'};
char data_types[][10] = {"double", "int", "char", "float"};
char special_symbols[12] = {'*', ';', ':', '.', ',', '^', '&',
'!', '>', '<', '~', '`'};


enum TYPE {
    IDENTIFIER,
    KEYWORD,
    STRING_LITERAL,
    NUMERIC_CONSTANT,
    OPERATOR,
    BRACKET,
    SPECIAL_SYMBOL,
    RELATIONAL_OPERATOR,
    CHARACTER_CONSTANT
};

char types[][30] = {"IDENTIFIER", "KEYWORD", "STRING_LITERAL",
                    "NUMERIC_CONSTANT", "OPERATOR", "BRACKET", "SPECIAL_SYMBOL",
                    "RELATIONAL_OPERATOR", "CHARACTER_CONSTANT"};


typedef struct symbol {
    char *name;
    char *data_type;
    unsigned int size;
    struct symbol *next;
} Symbol;



typedef struct node {
    char *cur;
    int row, col;
    enum TYPE type;
    struct node *next;
} Node;

int isKeyword(char buffer[]){
    for(int i=0;i<32;i++){
        if(strcmp(buffer, keywords[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int isDatatype(char buffer[]){
    for(int i=0;i<4;i++){
        if(strcmp(buffer, data_types[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int isOperator(char ch){
    for(int i=0;i<5;i++){
        if(operators[i] == ch)
            return 1;
    }
    return 0;
}

int isBracket(char ch){
    for(int i=0;i<6;i++){
        if(brackets[i] == ch)
            return 1;
    }
    return 0;
}

int isSpecialSymbol(char c){
    for(int i=0;i<12;i++){
        if(special_symbols[i] == c)
            return 1;
    }
    return 0;
}




void displaySymbolTable() {
    printf("\nSymbol table (in the format < Name , Type , Size > ): \n\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        Symbol *cur = st[i].head;
        while (cur) {
            printf(" %8s\t %8s\t %8d\t \n", cur->name, cur->data_type, cur->size);
            cur = cur->next;
        }
    }
}

int searchSymbolTable(char identifier[], char data_type[]) {
    int index = strlen(identifier) % MAX_SIZE;
    Symbol *cur = st[index].head;
    int i = 0;
    while (cur != NULL) {
        if (strcmp(identifier, cur->name) == 0)
            return i;
        cur = cur->next;
        i++;
    }
    return -1;
}

int searchLinkedList(LinkedList *list, char buffer[]) {
    Node *cur = list->head;
    while (cur != NULL) {
        if (strcmp(cur->cur, buffer) == 0)
            return 1;
        cur = cur->next;
    }
    return 0;
}

void insertSymbolTable(char identifier[], char data_type[]) {
    int index = strlen(identifier) % MAX_SIZE;
    if (searchSymbolTable(identifier, data_type) == -1) {
        Symbol *n = (Symbol *)malloc(sizeof(Symbol));
        n->name = strdup(identifier);
        n->next = NULL;
        n->data_type = strdup(data_type);
        if (strcmp(data_type, "int") == 0)
            n->size = 4;
        else if (strcmp(data_type, "double") == 0)
            n->size = 8;
        else if (strcmp(data_type, "char") == 0)
            n->size = 1;
        else if (strcmp(data_type, "function") == 0)
            n->size = 0;
        else
            n->size = 4;
        if (st[index].head == NULL) {
            st[index].head = n;
            return;
        }
        Symbol *cur = st[index].head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = n;
    }
}

void insertLinkedList(LinkedList *list, char buffer[], int row, int col, TYPE type) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->cur = strdup(buffer);
    newNode->row = row;
    newNode->col = col;
    newNode->type = type;
    newNode->next = list->head;
    list->head = newNode;
}

void insertHashTable(char buffer[], int row, int col, TYPE type) {
    int index = strlen(buffer) % MAX_SIZE;
    if (type == IDENTIFIER || !searchLinkedList(&hashTable[index], buffer)) {
        printf("<%s,%d,%d,%s>\n", buffer, row, col, types[type]);
        insertLinkedList(&hashTable[index], buffer, row, col, type);
    }
}
LinkedList hashTable[MAX_SIZE];

int main() {
    removeSpaces();
    int rowNum = preProcessIgnore();
    LinkedList hashTable[MAX_SIZE];
    SymbolLinkedList st[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++) {
        initializeLinkedList(&hashTable[i]);
        initializeSymbolLinkedList(&st[i]);
    }

    FILE *fin = fopen("output1.c", "r");
    if(fin == NULL){
        printf("Cannot open file!\n");
        return 0;
    }

    char buffer[100], c = 0, data_type_buffer[100];
    int i = 0, col_global = 1, col, temp_row = --rowNum;
    while(temp_row > 0){
        c = fgetc(fin);
        if(c == '\n')
            temp_row--;
    }

    while(c != EOF){
        if(isalpha(c) != 0 || c == '_'){
            buffer[i++] = c;
            col = col_global;
            while(isalpha(c) != 0 || c == '_' || isdigit(c) != 0){
                c = fgetc(fin);
                col_global++;
                if (isalpha(c) != 0 || c == '_' || isdigit(c) != 0)
                    buffer[i++] = c;
            }

            buffer[i] = '\0';

            if(isDatatype(buffer) == 1){
                insertHashTable(buffer, rowNum, col-1, KEYWORD);
                strcpy(data_type_buffer, buffer);
            }
            else if(isKeyword(buffer) == 1){
                insertHashTable(buffer, rowNum, col-1, KEYWORD);
            }
            else{
                insertHashTable(buffer, rowNum, col-1, IDENTIFIER);
                if(c == '(')
                    insertSymbolTable(buffer, "function");
                else
                    insertSymbolTable(buffer, data_type_buffer);
                data_type_buffer[0] = '\0';
            }

            i = 0;
            if(c == '\n') 
                rowNum++, col_global = 1;
            buffer[0] = '\0';
        }
        else if(isdigit(c) != 0){
            buffer[i++] = c;
            col = col_global;
            while(isdigit(c) != 0 || c == '.'){
                c = fgetc(fin);
                col_global++;
                if(isdigit(c) != 0 || c == '.')
                    buffer[i++] = c;
            }
            buffer[i] = '\0';
            insertHashTable(buffer, rowNum, col-1, NUMERIC_CONSTANT); // numerical constant
            i = 0;
            if(c == '\n') 
                rowNum++, col_global = 1;
            buffer[0] = '\0';
        }
        else if(c == '\"'){
            col = col_global;
            buffer[i++] = c;
            c = 0;
            while(c != '\"'){
                c = fgetc(fin);
                col_global++;
                buffer[i++] = c;
            }
            buffer[i] = '\0';
            insertHashTable(buffer, rowNum, col-1, STRING_LITERAL); // string literals
            buffer[0] = '\0';
            i = 0;
            c = fgetc(fin);
            col_global++;
        }
        else if(c == '\''){
            col = col_global;
            buffer[i++] = c;
            c = 0;
            c = fgetc(fin);
            col_global++;
            buffer[i++] = c;
            if(c == '\\'){
                c = fgetc(fin);
                col_global++;
                buffer[i++] = c;
            }
            c = fgetc(fin);
            col_global++;
            buffer[i++] = c;
            buffer[i] = '\0';
            insertHashTable(buffer, rowNum, col-1, CHARACTER_CONSTANT); //character constants
            buffer[0] = '\0';
            i=0;
            c = fgetc(fin);
            col_global++;
        }
        else{
            col = col_global;
            if(c == '='){ // relational and logical operators
                c = fgetc(fin);
                col_global++;
                if(c == '='){
                    insertHashTable("==", rowNum, col-1, RELATIONAL_OPERATOR);
                }
                else{
                    insertHashTable("=", rowNum, col-1, RELATIONAL_OPERATOR);
                    fseek(fin, -1, SEEK_CUR);
                    col_global--;
                }
            }
            else if(c == '>' || c == '<' || c == '!'){
                char temp = c;
                c = fgetc(fin);
                col_global++;
                if(c == '='){
                    char temp_str[3] = {temp, '=', '\0'};
                    insertHashTable(temp_str, rowNum, col-1, RELATIONAL_OPERATOR);
                }
                else{
                    char temp_str[2] = {temp, '\0'};
                    insertHashTable(temp_str, rowNum, col-1, RELATIONAL_OPERATOR);
                    fseek(fin, -1, SEEK_CUR);
                    col_global--;
                }
            }
            else if(isBracket(c) == 1){
                char temp_string[2] = {c,'\0'};
                insertHashTable(temp_string, rowNum, col-1, BRACKET);
            }
            else if(isSpecialSymbol(c) == 1){
                char temp_string[2] = {c,'\0'};
                insertHashTable(temp_string, rowNum, col-1, SPECIAL_SYMBOL);
            }
            else if(isOperator(c) == 1){
                char temp = c;
                c = fgetc(fin);
                col_global++;
                if (c == '=' || (temp == '+' && c == '+') || (temp == '-' && c == '-')){
                    char temp_string[3] = {temp,c,'\0'};
                    insertHashTable(temp_string, rowNum, col-1, OPERATOR);
                }
                else{
                    char temp_String[2] = {temp,'\0'};
                    insertHashTable(temp_String, rowNum, col-1, OPERATOR);
                    fseek(fin, -1, SEEK_CUR);
                    col_global--;
                }
            }
            else if(c == '\n') 
                rowNum++, col_global = 1;
            c = fgetc(fin);
            col_global++;
        }
    }
    displaySymbolTable();

    return 0;
}
