/*
 * @file cus_string.h
 * @author Arjun Pathak
 * @brief String Header file with function declarations
 *
 * This file contains the function declarations for the custom string
 * implementation that is being used by all prefix/suffix trees in this
 * project. The string thus created supports appending and duplicaion.
 * When there isn't enough capacity in the underlying array, a new one
 * with double the size of the previous is re-allocated in it's place.
*/

#ifndef STRING_H
#define STRING_H

/**
 * @struct string
 * @brief This structure is a custom string type for prefix matching.
 *
 * @var string::array
 * Member array is the underlying character array that stores all the characters of the string.
 * @var string::length
 * Member length keeps track of the number of non null characters in the string, saves time by.
 * avoiding strlen() calls
 * @var capacity
 * Member capacity keeps track of the capacity of the underlying char array.
 */

struct string {
    char *array;
    int length;
    int capacity;
};
typedef struct string string;

/**
 * @brief Creates a string out of the given params.
 *
 * @param[in] array
 * @param[int] length
 * @param[out] str
*/

string *initString(char *array, int length);

/**
 * @brief Appends a new character to the end of an existing string.
 * 
 * @param[in,out] str
 * @param[in] c
 */

void append(string* str, char c);

/**
 * @brief Duplicated a strings and returns the new one.
 *
 * @param[int] str
 * @param[out] duplicate
 */

string* duplicate(string* str);

/**
 * @brief Reclaims the memory allocated to the string.
 *
 * @param[in] str
 */

void delString(string *str);

/**
 * @brief Takes in a string and sanitizes it to remove unwanted characters.
 *
 * @param[in, out] str The string that has to be sanitized.
 */
void sanitize(string *str);

#endif
