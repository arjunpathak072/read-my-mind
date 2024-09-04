/*
 * @file string.h
 * @author Arjun Pathak
 * @brief String Header file with function declarations
 *
 * This file contains the function declarations for the custom string
 * implementation that is being used by all prefix/suffix trees in this
 * project. The string thus created supports appending and duplicaion.
 * When there isn't enough capacity in the underlying array, a new one
 * with double the size of the previous is re-allocated in it's place.
*/

struct string {
    char *array;
    int length;
    int capacity;
};
typedef struct string string ;

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
*/

string *initString(char *array, int length);

/**
 * @brief Appends the given character to the given string
 * 
 * This function takes in a string and appends the given character to
 * it. Appending to a string may trigger a resize under the hood, which
 * will double the capacity of the underlying array, while accounting
 * for the '\0' character in the end.
 *
 * @param[in,out] str
 * @param[in] c
 */
void append(string* str, char c);

/**
 * @brief Duplicated a strings and returns the new one
 *
 * This function takes in a string, duplicates it, and then returns the
 * duplciate that was created. The duplicate has the same length, capacity
 * and a deep copy of the original's array.
 *
 * @param[int] str
 * @param[out] duplicate
 */
string* duplicate(string* str);

/**
 * @brief Deallocates memory being used by a string
 *
 * This function should be called by the client after a string has done
 * its job. The function deallocates the allocated array, followed by the
 * string itself.
 *
 * @param[in] str
 */
void delString(string *str);
