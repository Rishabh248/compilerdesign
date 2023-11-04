#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <math.h>

// Symbol table entry structure
struct SymbolEntry {
    int sl_no;
    char token_name[20];
    char token_type[20];
    char returntype[20];
    char datatype[20];
    int no_of_args;
};

// Function to search for duplicate entries in the symbol table
int isDuplicate(struct SymbolEntry table[], int size, const char *token_name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(table[i].token_name, token_name) == 0) {
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicate found
}

int main() {
    struct SymbolEntry symbolTable[100]; // Maximum of 100 entries
    int tableSize = 0;

    // Read entries from a file (simplified input)
    FILE *file = fopen("file.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fscanf(file, "%d %s %s %s %s %d",
                  &symbolTable[tableSize].sl_no,
                  symbolTable[tableSize].token_name,
                  symbolTable[tableSize].token_type,
                  symbolTable[tableSize].returntype,
                  symbolTable[tableSize].datatype,
                  &symbolTable[tableSize].no_of_args) == 6) {

        // Check for duplicate entry
        if (isDuplicate(symbolTable, tableSize, symbolTable[tableSize].token_name)) {
            printf("Duplicate entry found: %s\n", symbolTable[tableSize].token_name);
        } else {
            tableSize++;
        }
    }

    fclose(file);

    // Print the symbol table (for demonstration)
    printf("Symbol Table:\n");
    for (int i = 0; i < tableSize; i++) {
        printf("%d %s %s %s %s %d\n",
               symbolTable[i].sl_no,
               symbolTable[i].token_name,
               symbolTable[i].token_type,
               symbolTable[i].returntype,
               symbolTable[i].datatype,
               symbolTable[i].no_of_args);
    }

    return 0;
}
