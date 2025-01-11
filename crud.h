#ifndef CRUD_OPERATIONS_H
#define CRUD_OPERATIONS_H

#include "DS.h"

void saveStateForUndo(Node *head);
void undo(Node **head);
void redo(Node **head);
void readFileIntoBuffer(Node **head, FILE *file);
void writeFileFromBuffer(Node *head, FILE *file);
void searchAndReplaceWord(Node *head, const char *searchWord, const char *replaceWord);
int searchWordInBuffer(Node *head, const char *word);

#endif

