/**
 * @file string.c
 * @brief Provides the implementation for all functions declared in the string.h header file.
 * @author Arjun Pathak
 * 
 * This file contains the implementations of all functions that are declared in the string.h
 * header file. This is a tailored string implementation that will be used by all prefix/suffix
 * trees in this project. This custom string type allows me to easily append and duplicate strings
 * on the fly, which was a bit clumsy when doing it the vailla C way (of using char arrays).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/string.h"

/**
 * @brief Creates a string out of the given params
 *
 * This functions takes in a null terminated character array and
 * its length, allocates a new string type struct on heap with 
 * length, capacity and array fields initialized based on the input
 * parameters and returns it.
 *
 * @param[in] array
 * @param[int] length
 * @param[out] str
 *
 * @return Returns a pointer to the newly allocated string.
*/

string *initString(char* array, int length) {
    string *str = (string *) malloc(sizeof(string));
    str->array = (char *) malloc(sizeof(char) * (length+1));
    strcpy(str->array, array);
    str->capacity = length+1;
    str->length = length;
}

/**
 * @brief This helper function is used to resize the underlying char array.
 *  
 * The function is relatively simple. It takes in a pointer to string type
 * and doubles its capacity (while compensating for the \0 character), copies
 * over the contents from the previous array, and reassigns. The function uses
 * realloc to achieve this behaviour. If a NULL pointer is passed into the function
 * , it acts as simple malloc.
 *
 * @param[in, out] input The string that needs to be resized.
 */

static void resize(string *input) {
    int newCapacity = input->length*2 + 1;
    input->array = (char *) realloc(input->array, newCapacity * sizeof(char)); 
    input->capacity = newCapacity;
}

/**
 * @brief Appends a new character to the end of an existing string.
 *
 * This function takes in a character and a string, and appends the former to
 * the latter. If the string does not have enough room for one more character,
 * a resize of the underlying char array is triggered and the capacity and length
 * fields are updated accordingly.
 *
 * @param[in] input The original string.
 * @param[in] c The character that will be appended.
 */

void append(string *input, char c) {
    if (input->length+1 == input->capacity) {
        resize(input);
    }
    input->array[input->length++] = c;
    input->array[input->length] = '\0';
}

/**
 * @brief Duplicates a strings and returns the new one.
 * 
 * This function takes in a string type variable, created a deep copy of it
 * and returns the newly created one to the caller.
 *
 * @param[int] str
 * @param[out] duplicate
 * 
 * @return Returns the newly allocated string, which is a deep copy of the first in parameter.
 */

string *duplicate(string *input) {
    string *dupString = malloc(sizeof(string));
    dupString->array = malloc(input->capacity * sizeof(char));
    
    strcpy(dupString->array, input->array);
    dupString->capacity = input->capacity;
    dupString->length = input->length;
    
    return dupString;
}

/**
 * @brief Reclaims the memory allocated to the string.
 *
 * This function calls free on the string that is passed into it, after it has
 * freed the underlying char array.
 *
 * @param[int] input The string that needs to be deleted.
 */

void delString(string *input) {
    free(input->array);
    free(input);
}

/**
 * @brief Sanitizes the input string to remove unwanted characters from it
 *
 * This functions changes the underlying array to get rid of unwanted characters in the query. The
 * prefix matching happens only for the english alphabet and happens to be case insensitive. This
 * function makes sure that all characters fall into that bracket.
 *
 * @param[in, out] input The string that is to be sanitized. The array is reallocated in place.
 */

void sanitize(string *input) {
    char *sanitized = malloc(sizeof(char) * input->capacity);
    int itr = 0;
    for (int i = 0; i <= input->length; i++) {
        if (input->array[i] >= 'a' && input->array[i] <= 'z') {
            sanitized[itr++] = input->array[i];
        } else if (input->array[i] >= 'A' && input->array[i] <= 'Z') {
            sanitized[itr++] = input->array[i] + 32;
        }
    }
    
    sanitized[itr] = '\0';
    input->length = itr;
    free(input->array);
    input->array = sanitized;
}

/**
 * @brief This function is used to test the custom string types and all
 * supported operations
 */

static void testString() {
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
