/*
    Definition of the custom string implementation for optimized append,
    duplicate and pop operations into char arrays.
    The implementation maintains a length and a capacity field to only resize when needed.
*/
struct string {
    char *array;
    int length;
    int capacity;
};
typedef struct string string ;

// takes a string and a character and appends the character to the string
void append(string*, char);

// takes a string and returns a pointer to a heap alllocated duplicate of it
string* duplicate(string*);

// test cases for the custom string implementation
void testString();
