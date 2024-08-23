/*
    Definition of the custom string implementation for optimized append,
    duplicate and pop operations into char arrays
*/
struct string {
    char *array;
    int size;
};
typedef struct string string ;

// takes a string and a character and appends the character to the string
void append(string*, char);

// takes a string and returns a pointer to a heap alllocated duplicate of it
string* duplicate(string*);

// takes a string and removes the last element (does not shrink the array)
void pop(string *);

// test cases for the custom string implementation
void testString();