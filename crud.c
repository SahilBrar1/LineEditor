#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"


// void saveStateForUndo(Node *head) {
//     pushOperation(&undoStack, head);  // yahan pe current state save krenge
// }

void readFileIntoBuffer(Node **head, FILE *file) {
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        insertLine(head, line);
    }
}

void writeFileFromBuffer(Node *head, FILE *file) {
    while (head != NULL) {
        for (int i = 0; i < head->wordCount; i++) {
            fprintf(file, "%s ", head->words[i]);
        }
        fprintf(file, "\n");
        head = head->next;
    }
}

void searchAndReplaceWord(Node *head, const char *searchWord, const char *replaceWord) {
    int lineNo = 1;
    while (head != NULL) {
        for (int i = 0; i < head->wordCount; i++) {
            if (strcmp(head->words[i], searchWord) == 0) {
                head->words[i] = strdup(replaceWord);
                printf("Replaced word '%s' with '%s' in line %d.\n", searchWord, replaceWord, lineNo);
            }
        }
        head = head->next;
        lineNo++;
    }
}

int searchWordInBuffer(Node *head, const char *word) {
    int lineNo = 1;
    while (head != NULL) {
        for (int i = 0; i < head->wordCount; i++) {
            if (strcmp(head->words[i], word) == 0) {
                printf("Word '%s' found at line %d, word index %d.\n", word, lineNo, i);
                return lineNo;
            }
        }
        head = head->next;
        lineNo++;
    }
    printf("Word '%s' not found in buffer.\n", word);
    return -1;
}
