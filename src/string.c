#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/string.h"

string *initString(char* array, int length) {
    string *str = (string *) malloc(sizeof(string));
    str->array = (char *) malloc(sizeof(char) * (length+1));
    strcpy(str->array, array);
    str->capacity = length+1;
    str->length = length;
}

static void resize(string *input) {
    int newCapacity = input->length*2 + 1;
    input->array = (char *) realloc(input->array, newCapacity * sizeof(char)); 
    input->capacity = newCapacity;
}

void append(string *input, char c) {
    if (input->length+1 == input->capacity) {
        resize(input);
    }
    input->array[input->length++] = c;
    input->array[input->length] = '\0';
}

string *duplicate(string *input) {
    string *dupString = malloc(sizeof(string));
    dupString->array = malloc(input->capacity * sizeof(char));
    
    strcpy(dupString->array, input->array);
    dupString->capacity = input->capacity;
    dupString->length = input->length;
    
    return dupString;
}

void delString(string *input) {
    free(input->array);
    free(input);
}

void testString() {
    char *demo = "demo string";
    int demoLength = strlen(demo);

    string *str = initString(demo, demoLength);
    printf("past init phase\n");
    assert(str->capacity == demoLength+1);
    assert(str->length == demoLength);
    printf("initString successful\n");

    append(str, 'a');
    append(str, 'b');
    append(str, 'c');
    
    printf("append successful\n");
    assert(strcmp(str->array, "demo stringabc") == 0);
    assert(str->length == strlen("demo stringabc"));
    
    string *dup = duplicate(str);
    printf("duplication successful\n");
    
    assert(strcmp(dup->array, str->array) == 0);
    assert(dup->length == str->length);
    assert(dup->capacity == str->capacity);
    
    append(dup, '1');
    append(dup, '2');
    append(dup, '3');
    
    printf("appending to duplicate successful\n");
    delString(str);
    delString(dup);
}

int main() {
    testString();
}
