#include <stdbool.h>
#include "../include/string.h"

struct Node {
    struct Node* children[26];
    bool isEndOfWord;
};
typedef struct Node Node;

Node *init();
void insert(Node *, const char *);
void predict(Node *, string *);
void testTrie();