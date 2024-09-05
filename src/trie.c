/**
 * @file trie.c
 * @author Arjun Pathak
 * @brief This file contains the trie implementation for prefix matching.
 *
 * This file contains the implementations of functions defined in the
 * trie.h header file. This implementation of trie supports adding
 * strings to the trie by calling the insert method and then querying
 * the structure for prefix matches which returns all the possible 
 * words that are in the trie.
 */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../include/trie.h"
#include "../include/queue.h"

/**
 * @brief This function is used to create a new trie node.
 * 
 * The function heap allocates a new node, all the children of the
 * new node is initialized to NULL. The endOfWord marker is set to
 * false.
 *
 * @param[out] newNode The new node that is created by the function.
 */

static Node* createNode() {
    Node *newNode = (Node *)malloc(sizeof(Node));  
    newNode->isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

/**
 * @brief Used to create the root node of the trie.
 *
 * This is a wrapper around the createNode() function. It simply
 * creates a new Trie node and returns it to the caller. The node
 * is heap allocated.
 *
 * @paramp[out] newNode The new node which is returned by the createNode() function.
 */

Node *initTrie() {
    return createNode();
}

/**
 * @brief Used to reclaim all the heap allocated memory from Trie.
 *
 * This function is used to recursively delete all trie nodes starting
 * at the root. It traverses down the Trie and frees upwards. The root
 * node is also deleted in the process at the very end.
 *
 * @param[in] node The root of the trie to be deleted.
 */

Node *delTrie(Node *node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            delTrie(node->children[i]);
        }
    }
    free(node);
}

/**
 * @brief Used to insert a new word into the Trie.
 *
 * This function is used to insert a new word into the Trie. It startes by
 * creating a pointer to the root of the tree (passed in as a parameter) and
 * traverses it down the trie, setting NULL pointers in the path to a new Trie
 * Node.
 *
 * @param[in] root The root of the Trie.
 * @param[in] word The word to be inserted in the Trie.
 * 
 * @pre word is '\0' terminated.
 */

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

/**
 * @brief A helper function that returns all the matching words from the Trie.
 *
 * This function takes in a pointer to the last Trie Node that was successfully
 * matched with the corresponding letter in the search query. It then recursiively
 * calls itself until it reaches the end of a word, and then prints it to the stdout.
 *
 * @param[in] current Pointer to end of the prefix match Trie Nod.e
 * @param[in] prefix The prefix that has been matched thus far.
 */

static void walk(Node *current, string *prefix) {
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

/**
 * @brief Prints out the matches based on a search query.
 *
 * This function takes in the root of the Trie and the word that
 * is to be prefix matched. It then calls the walk helper function
 * which does a DFS on the Trie structure and prints out the sequence
 * if it happens to be the end of a word. This function will print out
 * all matching words from the Trie.
 *
 * @param[in] root The root of the Triei.
 * @param[word] The search query that is to be matched.
 *
 * @pre The trie needs to be populated.
 */

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

/**
 * @brief This functions returns the first N number of predictions from the Trie
 *
 * This function performs a BFS on the Trie structure. It starts from the last matching node in the
 * trie with the word input and returns a list of prefix matches. The strings are C style null
 * terminated char arrays.
 *
 * @param[in] root Root of the Trie Node.
 * @param[in] word The word to be prefix matched.
 * @param[in] results The number of results that the caller expects.
 * @param[out] resultsBuffer A buffer to hold the words that successfully matched.
 */

char **predictN(Node *root, string *word, int results) {
    char **resultsBuffer = malloc(sizeof(char *) * results);

    struct Entity {
        Node *currTrieNode;
        string *currPrefix;
    };
    typedef struct Entity Entity;

    Node *itr = root;
    int count = 0;
    for (int i = 0; i < word->length; i++) {
        int index = word->array[i] - 'a';
        if (itr->children[index] != NULL) {
            itr = itr->children[index];
            count++;
        } else {
            break;
        }
    }
    string *prefix = duplicate(word);
    prefix->array[count] = '\0';
    prefix->length = count;

    Entity *e = malloc(sizeof(Entity));
    e->currTrieNode = itr;
    e->currPrefix = prefix;
    Queue *queue = initQueue(e);
    
    int matches = 0;
    while (queue->front && matches != results) {
        Entity *frontValue = queue->front->value;

        if (frontValue->currTrieNode->isEndOfWord == true) {
            char *match = malloc(frontValue->currPrefix->length + 1);
            strcpy(match, frontValue->currPrefix->array);
            resultsBuffer[matches++] = match;
        } else {
            for (int i = 0; i < 26; i++) {
                if (frontValue->currTrieNode->children[i] != NULL) {
                    Entity *newEntity = malloc(sizeof(Entity));
                    newEntity->currTrieNode = frontValue->currTrieNode->children[i];
                    string *newPrefix = duplicate(frontValue->currPrefix);
                    append(newPrefix, i + 'a');
                    newEntity->currPrefix = newPrefix;
                    
                    addToQueue(queue, newEntity);
                }
            }
        }
        delString(frontValue->currPrefix);
        free(frontValue);
        removeFromQueue(queue);
    }
    if (queue->front == NULL) {
        deleteQueue(queue);
        return resultsBuffer;
    }
    QueueNode *temp = queue->front;
    while (temp != NULL) {
        Entity *frontValue = temp->value;
        delString(frontValue->currPrefix);
        free(frontValue);
        temp = temp->next;
    }
    deleteQueue(queue);

    return resultsBuffer;
}

/**
 * @brief A function to test the Trie Structure and all supported operations on it.
 */

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
        "tele",
        "t",
        "tel",
        "abc",
        "telep"
    };
    
    for (int i = 0; i < nTests; i++) {
        printf("prediction for %s:\n", tests[i]);
        string *query = initString(tests[i], strlen(tests[i]));
        char **buffer = predictN(root, query, 2);
        for (int i = 0; i < 2; i++) {
            printf("%s ", buffer[i]);
        }
        printf("\n");
        for (int i = 0; i < 2; i++) {
            free(buffer[i]);
        }
        free(buffer);
        delString(query);
    }
    delTrie(root);
}
