#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/string.h"

void append(string *input, char c) {
    if (!input) {
        input = malloc(sizeof(string));
        input->size = 0;
        input->array = "";
    }
    int length = strlen(input->array);
    
    if (length + 1 == input->size) {
        int newSize = 2*length + 1;
        char *temp = (char *) malloc(newSize * sizeof(char));
        
        if (temp == NULL) {
            printf("error allocating memory\n");
            exit(1);
        }
        
        memcpy(temp, input->array, length * sizeof(char));
        temp[length] = c;
        temp[length + 1] = '\0';
        free(input->array);
        input->array = temp;
        input->size = newSize;
    } else {
        input->array[length] = c;
        input->array[length + 1] = '\0';
    }
}

string *duplicate(string *input) {
    string *dupInput = malloc(1 * sizeof(string));
    char *dupArray = malloc(input->size * sizeof(char));
    
    if (dupArray == NULL) {
        printf("error allocating memory\n");
        exit(1);
    }
    memcpy(dupArray, input->array, input->size);
    
    dupInput->array = dupArray;
    dupInput->size = input->size;
    
    return dupInput;
}

void pop(string *input) {
    input->array[input->size - 1] = '\0';
}

void testString() {
    string word;
    word.array = "apples";
    word.size = strlen(word.array)+1;
    append(&word, 'a');
    
    assert(word.size == 13);
    assert(strlen(word.array) == 7);
    assert(strcmp(word.array, "applesa") == 0);
    
    string* dup = duplicate(&word);
    assert(strcmp(dup->array, word.array) == 0);
    
    free(dup);
}