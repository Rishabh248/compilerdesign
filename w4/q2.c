#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Node {
    char *cur;
    int row, col;
    struct Node *next;
    enum TYPE type;
} Node;

typedef struct Symbol {
    char *name;
    char *data_type;
    struct Symbol *next;
    unsigned int size;
} Symbol;

Node *symbolTable = NULL; 
Symbol *st = NULL;     

// Inserting elements in the linked list
void insertLinkedList(Node **list, char buffer[], int row, int col, enum TYPE type) {
    Node *n = (Node *)malloc(sizeof(Node));
    char *str = (char *)calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(str, buffer);
    n->cur = str;
    n->next = NULL;
    n->row = row;
    n->col = col;
    n->type = type;

    if (*list == NULL) {
        *list = n;
    } else {
        Node *cur = *list;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = n;
    }
}

void insertSymbolTable(char identifier[], char data_type[]) {
    Symbol *n = (Symbol *)malloc(sizeof(Symbol));
    char *str = (char *)calloc(strlen(identifier) + 1, sizeof(char));
    strcpy(str, identifier);
    n->name = str;
    n->next = NULL;
    char *typee = (char *)calloc(strlen(data_type) + 1, sizeof(char));
    strcpy(typee, data_type);
    n->data_type = typee;

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

    if (st == NULL) {
        st = n;
    } else {
        Symbol *cur = st;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = n;
    }
}

int searchSymbolTable(char identifier[], char data_type[]) {
    Symbol *cur = st;
    int i = 0;
    while (cur != NULL) {
        if (strcmp(identifier, cur->name) == 0)
            return i;
        cur = cur->next;
        i++;
    }
    return -1;
}

int searchLinkedList(Node *list, char buffer[], enum TYPE type) {
    Node *cur = list;
    while (cur != NULL) {
        if (strcmp(cur->cur, buffer) == 0)
            return 1;
        cur = cur->next;
    }
    return 0;
}

// ... (Other functions remain the same)
