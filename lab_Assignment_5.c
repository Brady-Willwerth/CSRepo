#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

int length(node* head) {
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

char* toCString(node* head) {
    int len = length(head);
    char* str = (char*)malloc((len + 1) * sizeof(char)); // +1 for null terminator
    node* current = head;
    int i = 0;
    while (current != NULL) {
        str[i++] = current->letter;
        current = current->next;
    }
    str[i] = '\0'; // null terminator
    return str;
}

void insertChar(node** pHead, char c) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->letter = c;
    newNode->next = NULL;

    if (*pHead == NULL) {
        *pHead = newNode;
    } else {
        node* current = *pHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void deleteList(node** pHead) {
    node* current = *pHead;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    *pHead = NULL;
}

int main(void) {
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt", "r");
    if (inFile == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }
    fscanf(inFile, " %d\n", &numInputs); // Read the number of inputs from the file
    while (numInputs-- > 0) {
        fscanf(inFile, " %d\n", &strLen); // Read the length of the string from the file
        for (i = 0; i < strLen; i++) {
            fscanf(inFile, " %c", &c); // Read each character of the string from the file
            insertChar(&head, c); // Insert the character into the linked list
        }
        str = toCString(head); // Convert the linked list to a C string
        printf("String is: %s\n", str); // Print the resulting string
        free(str); // Free the memory allocated for the string
        deleteList(&head); // Delete the linked list
        if (head != NULL) {
            printf("deleteList is not correct!");
            break;
        }
    }
    fclose(inFile);
    return 0;
}