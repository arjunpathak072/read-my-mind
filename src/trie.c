#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../include/trie.h"

Node* createNode() {
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    if (newNode == NULL) {
        printf("error allocating memory\n");
        exit(1);
    }
  
    newNode->isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }
    
    return newNode;
}

Node *init() {
    return createNode();
}

void insert(Node *root, const char* word) {
    Node *current = root;
    while (*word != '\0') {
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
    if (current->isEndOfWord) {
        printf("%s\n", prefix->array);
        return;
    }
    
    for (int i = 0; i < 26; i++) {
        if (current->children[i]) {
            string *newPrefix = duplicate(prefix);
            append(newPrefix, 'a' + i);
            walk(current->children[i], newPrefix);
            free(newPrefix);
        }
    }
}

void predict(Node *root, string *word) {
    Node *itr = root;
    int count = 0;
    
    for (int i = 0; i < strlen(word->array); i++) {
        int idx = word->array[i] - 'a';
        if (itr->children[idx]) {
            itr = itr->children[idx];
            count++;
        } else {
            break;
        }
    }
    
    string *prefix = malloc(sizeof(string));
    prefix->array = malloc(word->size * sizeof(char));
    memcpy(prefix->array, word->array, (count*sizeof(char)));
    prefix->array[count] = '\0';
    prefix->size = word->size;
    
    // printf("%s, %d, %ld\n\n", prefix->array, prefix->size, strlen(prefix->array));
    walk(itr, prefix);
    free(prefix);
}

void testTrie() {
    char* words[] = {
        "apple",
        "banana",
        "ape",
        "apostle"
    };
    
    char *testCases[] = {
        "aa",
        "ap",
        "b",
        "ba",
    };
    Node *root = init();
    
    for (int i = 0; i < 4; i++) {
        insert(root, words[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        string word;
        word.array = testCases[i];
        word.size = strlen(testCases[i]) + 1;
        predict(root, &word);
        printf("\n");
    }
}