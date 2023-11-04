#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

int is_function_declaration(const char *line) {
    // Check if the line contains a function declaration
    return (strstr(line, "(") != NULL && strstr(line, ")") != NULL &&
            strstr(line, "(") < strstr(line, ")"));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s input_2.c\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int in_function = 0; 

    while (fgets(line, sizeof(line), file)) {
        // Remove whitespace
        char *trimmed_line = line;
        while (isspace(*trimmed_line)) {
            trimmed_line++;
        }
        size_t len = strlen(trimmed_line);
        while (len > 0 && isspace(trimmed_line[len - 1])) {
            trimmed_line[--len] = '\0';
        }

        if (is_function_declaration(trimmed_line)) {
            if (!in_function) {
                in_function = 1;
                printf("Function: %s\n", trimmed_line);
            }
        } else {
            in_function = 0;
        }
    }

    fclose(file);
    return 0;
}
