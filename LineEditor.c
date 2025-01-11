#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"
#include "DS.h"

// Function to display instructions
void displayInstructions() {
    printf("***********************************\n");
    printf("         Welcome to Line Editor    \n");
    printf("***********************************\n");
    printf("Available commands:\n");
    printf("1. insert_line      - Insert a new line\n");
    printf("2. insert_word      - Insert a word in a specific line\n");
    printf("3. remove_line      - Remove a specific line\n");
    printf("4. remove_word      - Remove a word from a specific line\n");
    printf("5. print            - Print all lines\n");
    printf("6. search           - Search for a word in the text\n");
    printf("7. replace          - Replace a word with another word\n");
    printf("8. modify_line      - Modify a specific line\n");
    printf("9. exit             - Exit the editor\n");
    printf("***********************************\n\n");
}

void handleCommand(Node **head, const char *command) {
    char buffer[256];
    char *operation = strtok(strdup(command), " ");

    if (strcmp(operation, "insert_line") == 0) {
        printf("Enter the line to insert: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        insertLine(head, buffer);
    } 
    else if (strcmp(operation, "insert_word") == 0) {
        int lineNumber, wordPosition;
        char word[MAX_WORD_LENGTH];
        printf("Enter line number: ");
        scanf("%d", &lineNumber);
        printf("Enter word position: ");
        scanf("%d", &wordPosition);
        printf("Enter word to insert: ");
        scanf("%s", word);
        insertWordAtPosition(*head, lineNumber - 1, word, wordPosition);
    } 
    else if (strcmp(operation, "remove_line") == 0) {
        int position;
        printf("Enter the line number to remove: ");
        scanf("%d", &position);
        removeLine(head, position - 1);
    } 
    else if (strcmp(operation, "remove_word") == 0) {
        int lineNumber, wordIndex;
        printf("Enter line number: ");
        scanf("%d", &lineNumber);
        printf("Enter word index: ");
        scanf("%d", &wordIndex);
        Node *line = *head;
        for (int i = 0; i < lineNumber - 1; i++) {
            line = line->next;
        }
        removeWordAtCursor(line, wordIndex);
    } 
    else if (strcmp(operation, "print") == 0) {
        printLines(*head);
    } 
    else if (strcmp(operation, "search") == 0) {
        char word[MAX_WORD_LENGTH];
        printf("Enter word to search: ");
        scanf("%s", word);
        searchWordInBuffer(*head, word);
    } 
    else if (strcmp(operation, "replace") == 0) {
        char searchWord[MAX_WORD_LENGTH], replaceWord[MAX_WORD_LENGTH];
        printf("Enter word to replace: ");
        scanf("%s", searchWord);
        printf("Enter new word: ");
        scanf("%s", replaceWord);
        searchAndReplaceWord(*head, searchWord, replaceWord);
    } 
    else if (strcmp(operation, "modify_line") == 0) {
        int lineNumber, cursorPos, endPos;
        char newContent[256];
        printf("Enter line number: ");
        scanf("%d", &lineNumber);
        printf("Enter cursor position: ");
        scanf("%d", &cursorPos);
        printf("Enter end position: ");
        scanf("%d", &endPos);
        getchar();  // Consume newline
        printf("Enter new content: ");
        fgets(newContent, sizeof(newContent), stdin);
        newContent[strcspn(newContent, "\n")] = 0;

        Node *line = *head;
        for (int i = 0; i < lineNumber - 1; i++) {
            line = line->next;
        }
        modifyLineFromCursor(line, cursorPos, endPos, newContent);
    } 
    else {
        printf("Invalid command. Type 'help' for a list of commands.\n");
    }

    free(operation);  // Free dynamically allocated memory
}

int main(int argc, char *argv[]) {
    Node *head = NULL;
    FILE *file = NULL;

    if (argc == 1) {
        file = fopen("file.txt", "w+");
    } else if (argc == 2) {
        file = fopen(argv[1], "r+");
        if (!file) {
            file = fopen(argv[1], "w+");
        }
    } else if (argc == 3) {
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s/%s", argv[2], argv[1]);
        file = fopen(filePath, "r+");
        if (!file) {
            file = fopen(filePath, "w+");
        }
    } else {
        printf("Invalid arguments.\n");
        return 1;
    }

    if (file) {
        readFileIntoBuffer(&head, file);
        fclose(file);
    }

    // Display instructions at the start
    displayInstructions();

    char command[256];
    while (1) {
        printf("\nEnter command (type 'exit' to quit): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Remove trailing newline
        if (strcmp(command, "exit") == 0) {
            break;
        }
        handleCommand(&head, command);
    }

    if (argc > 1) {
        file = fopen(argv[1], "w+");
        writeFileFromBuffer(head, file);
        fclose(file);
    }

    freeList(head);
    return 0;
}
