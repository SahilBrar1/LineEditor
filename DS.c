#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DS.h"

Node* createNode() {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->wordCount = 0;    
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertLine(Node **head, const char *line) {
    Node *newNode = createNode();
    char *word = strtok(strdup(line), " ");
    while (word != NULL && newNode->wordCount < MAX_WORDS_PER_LINE) {
        newNode->words[newNode->wordCount++] = word;
        word = strtok(NULL, " ");
    }

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void insertLineAtPosition(Node **head, const char *line, int position) {
    Node *newNode = createNode();
    char *word = strtok(strdup(line), " ");
    
    while (word != NULL && newNode->wordCount < MAX_WORDS_PER_LINE) {
        newNode->words[newNode->wordCount++] = word;
        word = strtok(NULL, " ");
    }

    if (position == 0) {
        newNode->next = *head;
        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        *head = newNode;
        return;
    }

    Node *temp = *head;
    int index = 0;
    
    while (temp != NULL && index < position - 1) {
        temp = temp->next;
        index++;
    }

    if (temp == NULL) {
        printf("Position out of bounds.\n");
        free(newNode); 
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    
    temp->next = newNode;
}

void insertWordAtPosition(Node *head, int lineNumber, const char *word, int wordPosition) {
    if (head == NULL || lineNumber < 0 || wordPosition < 0) {
        return;
    }

    Node *current = head;
    int currentLine = 0;

    while (current != NULL && currentLine < lineNumber) {
        current = current->next;
        currentLine++;
    }

    if (current == NULL || wordPosition > current->wordCount || wordPosition < 0) {
        return;
    }

    if (current->wordCount >= MAX_WORDS_PER_LINE) {
        return;
    }

    for (int i = current->wordCount; i > wordPosition; i--) {
        current->words[i] = current->words[i - 1];
    }

    current->words[wordPosition] = strdup(word);
    current->wordCount++;
}

void modifyLineFromCursor(Node *line, int cursorPos, int endPos, const char *newContent) {
    if (cursorPos < 0 || endPos >= line->wordCount || cursorPos > endPos) {
        printf("Invalid positions.\n");
        return;
    }

    for (int i = cursorPos; i <= endPos; i++) {
        free(line->words[i]);
        line->words[i] = NULL;
    }

    char *word = strtok(strdup(newContent), " ");
    int i = cursorPos;
    while (word != NULL && i <= endPos) {
        line->words[i++] = strdup(word);
        word = strtok(NULL, " ");
    }

    line->wordCount = (i > line->wordCount) ? i : line->wordCount;
}

void removeLine(Node **head, int position) {
    if (*head == NULL) {
        printf("The buffer is empty.\n");
        return;
    }

    Node *temp = *head;
    int index = 0;

    while (temp != NULL && index < position) {
        temp = temp->next;
        index++;
    }

    if (temp == NULL) {
        printf("Position out of bounds.\n");
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
}

void removeWordAtCursor(Node *lineNode, int wordIndex) {
    if (lineNode == NULL) {
        printf("The line does not exist.\n");
        return;
    }

    if (wordIndex < 0 || wordIndex >= lineNode->wordCount) {
        printf("Word index out of bounds.\n");
        return;
    }

    for (int i = wordIndex; i < lineNode->wordCount - 1; i++) {
        lineNode->words[i] = lineNode->words[i + 1];
    }

    lineNode->wordCount--;
}

void printLines(Node *head) {
    int lineIndex = 1;
    while (head != NULL) {
        printf("[Line %d]: ", lineIndex++);
        for (int i = 0; i < head->wordCount; i++) {
            if (head->words[i] != NULL) {
                printf("%s ", head->words[i]);
            }
        }
        printf("\n");
        head = head->next;
    }
}

void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* copyList(Node *head) {
    if (head == NULL) return NULL;
    
    Node *newHead = createNode();
    Node *current = newHead;
    Node *temp = head;

    while (temp != NULL) {
        for (int i = 0; i < temp->wordCount; i++) {
            current->words[i] = strdup(temp->words[i]);
        }
        current->wordCount = temp->wordCount;

        if (temp->next != NULL) {
            current->next = createNode();
            current->next->prev = current;
            current = current->next;
        }
        temp = temp->next;
    }

    return newHead;
}
