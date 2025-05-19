#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search(const char *id);
void add();
void delete(const char *target_id);

void search(const char *id) {
    FILE *fp = fopen("database1.csv", "r");

    if (fp == NULL) {
        printf("\n[!] Error opening file.\n");
        return;
    }

    char row[200];
    int found = 0;

    while (fgets(row, sizeof(row), fp)) {
        char *ids = strtok(row, ",");
        char *name = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *role = strtok(NULL, ",\n");

        if (strcmp(ids, id) == 0) {
            printf("\n📄 Record Found:\n");
            printf("------------------------\n");
            printf("ID     : %s\n", ids);
            printf("Name   : %s\n", name);
            printf("Email  : %s\n", email);
            printf("Role   : %s\n", role);
            printf("------------------------\n\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n[!] No record found for ID: %s\n\n", id);
    }

    fclose(fp);
}

void add() {
    char newrow[200];
    char id[20], name[50], email[50], role[20];

    printf("\n📝 Add New Record\n------------------------\n");

    printf("Enter ID    : ");
    fgets(id, sizeof(id), stdin);
    printf("Enter Name  : ");
    fgets(name, sizeof(name), stdin);
    printf("Enter Email : ");
    fgets(email, sizeof(email), stdin);
    printf("Enter Role  : ");
    fgets(role, sizeof(role), stdin);

    // Remove trailing newlines
    id[strcspn(id, "\n")] = '\0';
    name[strcspn(name, "\n")] = '\0';
    email[strcspn(email, "\n")] = '\0';
    role[strcspn(role, "\n")] = '\0';

    snprintf(newrow, sizeof(newrow), "\n%s,%s,%s,%s", id, name, email, role);

    FILE *fp = fopen("database1.csv", "a");
    if (fp == NULL) {
        printf("\n[!] Error opening database.\n");
    } else {
        fputs(newrow, fp);
        printf("\n✅ Record added successfully!\n\n");
        fclose(fp);
    }
}

void delete(const char *target_id) {
    FILE *fp = fopen("database1.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (fp == NULL || temp == NULL) {
        printf("\n[!] Error opening files.\n");
        return;
    }

    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char line_copy[200];
        strcpy(line_copy, line);
        char *file_id = strtok(line_copy, ",");

        if (file_id && strcmp(file_id, target_id) == 0) {
            found = 1;
            continue;  // Skip this line
        }

        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("database1.csv");
    rename("temp.csv", "database1.csv");

    if (found)
        printf("\n✅ Row with ID '%s' deleted successfully!\n\n", target_id);
    else
        printf("\n[!] No record found with ID: %s\n\n", target_id);
}

int main() {
    printf("\n============================================\n");
    printf("      📁 Welcome to the Database System\n");
    printf("============================================\n\n");

    int choice;
    char id[20];

    printf("1️⃣  Search a record\n");
    printf("2️⃣  Add a new record\n");
    printf("3️⃣  Delete an existing record\n");
    printf("🔢 Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear newline

    switch (choice) {
        case 1:
            printf("\n🔍 Enter the ID to search: ");
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = '\0';
            search(id);
            break;

        case 2: {
            int on = 1;
            while (on) {
                add();
                printf("🔁 Add another? (1 = Yes / 0 = Exit): ");
                scanf("%d", &on);
                getchar(); // Clear newline
            }
            break;
        }

        case 3:
            printf("\n❌ Enter the ID to delete: ");
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = '\0';
            delete(id);
            break;

        default:
            printf("\n[!] Invalid choice. Please run the program again.\n\n");
            break;
    }

    printf("👋 Exiting the program. Thank you!\n\n");
    return 0;
}
