#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../include/trie.h"

static Node* createNode() {
    Node *newNode = (Node *)malloc(sizeof(Node));  
    newNode->isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

Node *initTrie() {
    return createNode();
}

Node *delTrie(Node *node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            delTrie(node->children[i]);
        }
    }
    free(node);
}

void insert(Node *root, const char* word) {
    const char *temp = word;
    Node *current = root;
    while (*word != '\n' && *word != '\0') {
        int idx = *word - 'a';
        if (!current->children[idx]) {
            current->children[idx] = createNode();
        }
        current = current->children[idx];
        word++;
    }
    current->isEndOfWord = true;
}

void walk(Node *current, string *prefix) {
    if (*prefix->array == '\0') {
        return;
    }
    
    if (current->isEndOfWord) {
        printf("%s\n", prefix->array);
        return;
    }
    
    for (int i = 0; i < 26; i++) {
        if (current->children[i]) {
            string *newPrefix = duplicate(prefix);
            append(newPrefix, 'a' + i);
            walk(current->children[i], newPrefix);
            delString(newPrefix);
        }
    }
}

void predict(Node *root, string *word) {
    Node *itr = root;
    int count = 0;
    
    for (int i = 0; i < word->length; i++) {
        int idx = word->array[i] - 'a';
        if (itr->children[idx]) {
            itr = itr->children[idx];
            count++;
        } else {
            break;
        }
    }
    string *prefix = duplicate(word);
    prefix->array[count] = '\0';
    prefix->length = count;
    walk(itr, prefix);
    
    delString(prefix);
}

void testTrie() {
    int nWords = 3;
    char *words[3] = {
        "teleport",
        "telephone",
        "telegram",
    };
    Node *root = initTrie();
    for (int i = 0; i < nWords; i++) {
        insert(root, words[i]);
    }
    
    printf("inserted all words into the trie\n");
    
    int nTests = 5;
    char *tests[5] = {
        "t",
        "tele",
        "tel",
        "abc",
        "telep"
    };
    
    for (int i = 0; i < nTests; i++) {
        printf("prediction for %s:\n", tests[i]);
        string *query = initString(tests[i], strlen(tests[i]));
        predict(root, query);
        printf("\n");
        delString(query);
    }
    delTrie(root);
}

int main() {
    testTrie();
    return 0;
}
