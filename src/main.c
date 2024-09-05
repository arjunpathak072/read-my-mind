#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/trie.h"

int main(int argc, char *argv[]) {
    Node *root = initTrie();
    FILE *data;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    char input[45];
    
    data = fopen(argv[1], "r");
    int resultsCount = atoi(argv[2]);

    while ((read = getline(&line, &length, data)) != -1) {
        insert(root, line);
    }

    while(true) {
        scanf("%44s", input);

        string *query = initString(input, strlen(input));
        char **buffer = predictN(root, query, resultsCount);
    
        for (int i = 0; i < resultsCount; i++) {
            printf("%s ", buffer[i]);
        }
        printf("\n");

        for (int i = 0; i < resultsCount; i++) {
           free(buffer[i]); 
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
