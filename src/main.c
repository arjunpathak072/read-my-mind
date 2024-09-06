/**
 * @file main.c
 * @author Arjun Pathak
 * @brief Interactive CLI interface to prefix match searches in a given data set.
 *
 * The program expects two command line arguments, the first one being the path to the file where
 * the words are stored. The word database file must be newline terminated words of the english
 * language. The second argument is the number os results that are expected to be returned at max.
 * This file contains the driver code to parse the command line arguments and start the interactive
 * loop and then accept user input to search the Trie.
 */

#define INPUT_BUFFER_SIZE 100
#define EXIT_KEYWORD ":e"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

/**
 * @brief The function takes in command line arguments, opens a file, inserts all words into the
 * Trie and then takes in user inputs to query the Trie.
 *
 * @param[in] argc The number of command line arguments to be passed.
 * @param[out] argv An array to store all the command line arguments.
 */

int main(int argc, char *argv[]) {
    FILE *data;
    data = fopen(argv[1], "r");
    if (data == NULL) {
        printf("Error opening file: %d\n", errno);
        return -1;
    }

    int resultsCount = atoi(argv[2]);
    if (resultsCount == 0) {
        printf("Invalid input for numbers of results.\n");
        return -1;
    }

    printf("\nThis is an interactive playground to test out the Trie autocomplete functionality.\n");
    printf("Type out a word and hit enter to get suggestions based on the input. Enter :e to exit the program.\n");
    
    Node *root = initTrie();
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    char input[INPUT_BUFFER_SIZE];
    int wordsCount = 0;

    while ((read = getline(&line, &length, data)) != -1) {
        insert(root, line);
        wordsCount++;
    }
    
    printf("%d words added to the Trie from the file %s\n\n", wordsCount, argv[1]);

    while(true) {
        printf("---------------------------------------------\n");
        
        scanf("%99s", input);

        if (strcmp(input, EXIT_KEYWORD) == 0) {
            printf("Execution complete.\n");
            break;
        } 

        string *query = initString(input, strlen(input));
        char **buffer = predictN(root, query, resultsCount);

        for (int i = 0; i < resultsCount; i++) {
            if (buffer[i]) {
                printf("%s ", buffer[i]);
            }
        }
        printf("\n");

        for (int i = 0; i < resultsCount; i++) {
           if (buffer[i]) {
               free(buffer[i]); 
           }
        }
        
        free(buffer);
        delString(query);
    }

    delTrie(root);
    
    fclose(data);
    if (line) {
        free(line);
    }
    
    return 0;
}
