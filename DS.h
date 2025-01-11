#ifndef DS_H
#define DS_H

#define MAX_WORDS_PER_LINE 100
#define MAX_WORD_LENGTH 50
#define MAX_HISTORY_SIZE 3  

typedef struct Node {
    char *words[MAX_WORDS_PER_LINE];
    int wordCount;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Operation {
    Node *data;  // Snapshot of the current state (deep copy)
} Operation;

typedef struct UndoRedoStack {
    Operation operations[MAX_HISTORY_SIZE];
    int top;
} UndoRedoStack;

extern UndoRedoStack undoStack;
extern UndoRedoStack redoStack;

Node* createNode();
void modifyLineFromCursor(Node *line, int cursorPos, int endPos, const char *newContent);

void insertLine(Node **head, const char *line);
void insertLineAtPosition(Node **head, const char *line, int position);
void insertWordAtPosition(Node *head, int lineNumber, const char *word, int wordPosition);
void removeLine(Node **head, int position);
void removeWordAtCursor(Node *lineNode, int wordIndex);
void printLines(Node *head);
void freeList(Node *head);

Node* copyList(Node *head);  // for copy
void pushOperation(UndoRedoStack *stack, Node *head);
Node* popOperation(UndoRedoStack *stack);

#endif

