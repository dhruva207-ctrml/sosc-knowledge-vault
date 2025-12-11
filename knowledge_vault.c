#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_CONTENT 500
#define NOTES_FILE "notes.txt"

void create_note() {
    FILE *fp = fopen(NOTES_FILE, "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    char title[MAX_TITLE];
    char content[MAX_CONTENT];

    printf("Enter title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    printf("Enter content (single line): ");
    fgets(content, sizeof(content), stdin);
    content[strcspn(content, "\n")] = '\0';

    fprintf(fp, "TITLE:%s\n", title);
    fprintf(fp, "CONTENT:%s\n", content);
    fprintf(fp, "---\n");

    fclose(fp);
    printf("Note saved.\n");
}

void view_notes() {
    FILE *fp = fopen(NOTES_FILE, "r");
    if (!fp) {
        printf("No notes yet.\n");
        return;
    }

    char line[600];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void search_note() {
    FILE *fp = fopen(NOTES_FILE, "r");
    if (!fp) {
        printf("No notes found.\n");
        return;
    }

    char query[MAX_TITLE];
    printf("Enter title to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    char line[600];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "TITLE:", 6) == 0) {
            char title[MAX_TITLE];
            strcpy(title, line + 6);
            title[strcspn(title, "\n")] = '\0';

            if (strcmp(title, query) == 0) {
                found = 1;
                printf("\nFOUND NOTE:\n");
                printf("TITLE: %s\n", title);

                fgets(line, sizeof(line), fp); 
                printf("%s", line);
                break;
            }
        }
    }

    if (!found)
        printf("No matching note.\n");

    fclose(fp);
}

void edit_note() {
    FILE *fp = fopen(NOTES_FILE, "r");
    if (!fp) {
        printf("No notes found.\n");
        return;
    }

    char target[MAX_TITLE];
    printf("Enter title to edit: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = '\0';

    FILE *temp = fopen("temp.txt", "w");
    char line[600];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "TITLE:", 6) == 0) {
            char title[MAX_TITLE];
            strcpy(title, line + 6);
            title[strcspn(title, "\n")] = '\0';

            if (strcmp(title, target) == 0) {
                found = 1;
                char new_content[MAX_CONTENT];

                
                fprintf(temp, "TITLE:%s\n", title);

                printf("Enter new content: ");
                fgets(new_content, sizeof(new_content), stdin);
                new_content[strcspn(new_content, "\n")] = '\0';

                // Store updated content
                fprintf(temp, "CONTENT:%s\n", new_content);
                fprintf(temp, "---\n");

                // Skip old content + ---
                fgets(line, sizeof(line), fp);
                fgets(line, sizeof(line), fp);
                continue;
            }
        }
        fprintf(temp, "%s", line);
    }

    fclose(fp);
    fclose(temp);

    remove(NOTES_FILE);
    rename("temp.txt", NOTES_FILE);

    if (found)
        printf("Note updated.\n");
    else
        printf("Note not found.\n");
}

void delete_note() {
    FILE *fp = fopen(NOTES_FILE, "r");
    if (!fp) {
        printf("No notes found.\n");
        return;
    }

    char target[MAX_TITLE];
    printf("Enter title to delete: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = '\0';

    FILE *temp = fopen("temp.txt", "w");
    char line[600];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "TITLE:", 6) == 0) {
            char title[MAX_TITLE];
            strcpy(title, line + 6);
            title[strcspn(title, "\n")] = '\0';

            if (strcmp(title, target) == 0) {
                found = 1;

                // Skip this note entirely
                fgets(line, sizeof(line), fp); 
                fgets(line, sizeof(line), fp); 
                continue;
            }
        }
        fprintf(temp, "%s", line);
    }

    fclose(fp);
    fclose(temp);

    remove(NOTES_FILE);
    rename("temp.txt", NOTES_FILE);

    if (found)
        printf("Note deleted.\n");
    else
        printf("Note not found.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Personal Knowledge Vault ---\n");
        printf("1. Create note\n");
        printf("2. View all notes\n");
        printf("3. Search note\n");
        printf("4. Edit note\n");
        printf("5. Delete note\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        switch (choice) {
            case 1: create_note(); break;
            case 2: view_notes(); break;
            case 3: search_note(); break;
            case 4: edit_note(); break;
            case 5: delete_note(); break;
            case 6: printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
