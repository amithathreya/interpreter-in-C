#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_TOKEN_LENGTH 100
#define MAX_TOKENS 100

const char *keywords[] = {"if","else","while","let","throw","return"};
int num_words = sizeof(keywords)/sizeof(keywords[0]);

bool check(const char * word) {
    for (int i = 0; i < num_words; i++)
    {
        if(strcmp(word , keywords[i]) == 0) {
            return true;
        }
    } 
    return false;
}

void lexer(const char* input) {
    int index = 0; // Initialize index
    char word[50];
    for (size_t i = 0; input[i]!='\0' ;i++)
    {
        if(isspace(input[i]) || ispunct(input[i])) {
            if(index > 0) {
                word[index] = '\0';
                if(check(word)) {
                    printf("Keyword: %s\n", word);
                } else {
                    printf("Identifier: %s\n", word);
                }
                index = 0; // Reset index
            } 
            if (ispunct(input[i])) {
                printf("Punctuation: %c\n", input[i]);
            }
        } else {
            word[index++] = input[i];
        }
    }   
    if(index > 0) {
        word[index] = '\0';
        if(check(word)) {
            printf("Keyword: %s\n", word);
        } else {
            printf("Identifier: %s\n", word);
        }
    }
}

int main(int argc, char *argv[]) {
    char input[256];
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        while (fgets(input, sizeof(input), file)) {
            lexer(input);
        }
        fclose(file);
    } else {
        while (fgets(input, sizeof(input), stdin)) {
            lexer(input);
        }
    }
    return 0;
}
