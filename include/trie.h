/**
 * @file trie.h
 * @author Arjun Pathak
 * @brief Declaration of functions for the Trie implementation
 *
 * This header file contains the functions declarations for the Trie
 * data structure which will be used for prefix matching. The structure
 * supports insertion and prediction. The Trie type depends on the string
 * implementation declared in the string.h file, and implemented in the
 * string.c source file.
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include "cus_string.h"

/**
 * @struct Node
 * @brief This structure represents a single Trie Node
 *
 * @var Node::children[26]
 * Member children is a list of pointers to the next Trie Node. Each Node may lead to 26 others.
 * @var Node::isEndOfWord
 * Member isEndOfWord is a boolean value indicating if the current Node marks the end of a word or
 * not.
 */

struct Node {
    struct Node* children[26];
    bool isEndOfWord;
};
typedef struct Node Node;

/**
 * @brief This functions creates a new TrieNode and returns it to the caller.
 * 
 * @return newNode Returns the newly created Trie Node.
 */

Node *initTrie();

/**
 * @brief This function is used to insert a word into the Trie Structre.
 *
 * @param[in] root The root node of the Trie Structure.
 * @param[in] word The word that is to be inserted into the Trie.
 */

void insert(Node *root, const char *word);

/**
 * @brief This function is used to print to stdout, the matching words from
 * the Trie structure.
 *
 * @param[in] root The root of the Trie Node.
 * @param[in] word The word that is to be searched inside the Trie.
 */

void predict(Node *root, string *word);

/**
 * @brief This function returns the first N matching words in the trie for a given input word and N.
 *
 * @param[in] root Root node of the Trie.
 * @param[in] word Word to be prefix matched.
 * @param[in] resultsLength The number of results to be returned.
 *
 * @return The first resultsLength words returned matched in the Trie.
 */

char **predictN(Node *root, string *word, int resultsLength);

/**
 * @brief Takes in the root of the Trie and deletes all the nodes.
 * 
 * @param[in] root The root of the Trie.
 */

void delTrie(Node *root);

#endif
