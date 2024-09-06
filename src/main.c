#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/trie.h"

int main(int argc, char *argv[]) {
    printf("This is an interactive playground to test out the Trie autocomplete functionality\n");
    printf("Type out a word and hit enter to get suggestions based on the input\n");
    Node *root = initTrie();
    FILE *data;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    char input[45];
    
    data = fopen(argv[1], "r");
    int resultsCount = atoi(argv[2]);

    int wordsCount = 0;
    while ((read = getline(&line, &length, data)) != -1) {
        insert(root, line);
        wordsCount++;
    }
    
    printf("%d words added to the Trie from the file %s\n\n", wordsCount, argv[1]);

    while(true) {
        printf("---------------------------------------------\n");
        scanf("%44s", input);
        if (strcmp(input, "exit()") == 0) {
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
