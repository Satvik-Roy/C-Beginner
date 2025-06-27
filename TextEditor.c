#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum line length and number of lines (adjust as needed)
#define MAX_LINE_LENGTH 256
#define MAX_LINES 100

// Function to display the editor menu
void displayMenu() {
    printf("\nSimple Text Editor\n");
    printf("1. Create/Edit Text\n");
    printf("2. Save to File\n");
    printf("3. Load from File\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Function to handle text input and editing
void editText(char text[MAX_LINES][MAX_LINE_LENGTH], int *lineCount) {
    char input[MAX_LINE_LENGTH];
    printf("Enter text (press Enter on a blank line to finish):\n");
    *lineCount = 0;

    while (*lineCount < MAX_LINES) {
        fgets(input, MAX_LINE_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strlen(input) == 0) break; // Exit on blank line

        strncpy(text[*lineCount], input, MAX_LINE_LENGTH - 1);
        (*lineCount)++;
    }
}

// Function to save text to a file
void saveToFile(char text[MAX_LINES][MAX_LINE_LENGTH], int lineCount) {
    FILE *file = fopen("editor.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", text[i]);
    }
    fclose(file);
    printf("Text saved to editor.txt\n");
}

// Function to load text from a file
void loadFromFile(char text[MAX_LINES][MAX_LINE_LENGTH], int *lineCount) {
    FILE *file = fopen("editor.txt", "r");
    if (file == NULL) {
        printf("No file found or error opening file!\n");
        return;
    }

    *lineCount = 0;
    while (*lineCount < MAX_LINES && fgets(text[*lineCount], MAX_LINE_LENGTH, file) != NULL) {
        text[*lineCount][strcspn(text[*lineCount], "\n")] = 0; // Remove newline
        (*lineCount)++;
    }
    fclose(file);
    printf("Text loaded from editor.txt\n");
}

int main() {
    char text[MAX_LINES][MAX_LINE_LENGTH] = {0};
    int lineCount = 0;
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                editText(text, &lineCount);
                for (int i = 0; i < lineCount; i++) {
                    printf("%d: %s\n", i + 1, text[i]);
                }
                break;
            case 2:
                if (lineCount > 0) saveToFile(text, lineCount);
                else printf("No text to save!\n");
                break;
            case 3:
                loadFromFile(text, &lineCount);
                for (int i = 0; i < lineCount; i++) {
                    printf("%d: %s\n", i + 1, text[i]);
                }
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
