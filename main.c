#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void search(const char *id); // ✅ Add this prototype

void search(const char *id) {
    FILE *fp = fopen("database.csv", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char row[200];
    int value = 0;

    while(fgets(row, sizeof(row), fp)) {
        char *ids = strtok(row, ",");
        char *name = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *role = strtok(NULL, ",\n");

        if (strcmp(ids, id) == 0) {  //  Correct comparison
            printf("ID     : %s\n", ids);
            printf("Name   : %s\n", name);
            printf("Email  : %s\n", email);
            printf("Role   : %s\n", role);
            value = 1;
            break;
        }
    }

    if (!value) {
        printf("No record found for ID: %s\n", id);
    }

    fclose(fp);
}

void add(){

    char newrow[200];
    char id[20];
    char name[50];
    char email[50];
    char role[20];

    printf("Enter ID -->\n");
    fgets(id,sizeof(id),stdin);

    printf("Enter Name -->\n");
    fgets(name,sizeof(name),stdin);

    printf("Enter email -->\n");
    fgets(email,sizeof(email),stdin);

    printf("Enter role -->\n");
    fgets(role,sizeof(role),stdin);

    // removing new line characters from each string
    id[strcspn(id,"\n")]='\0';
    name[strcspn(name,"\n")]='\0';
    email[strcspn(email,"\n")]='\0';
    role[strcspn(role,"\n")]='\0';

    snprintf(newrow,sizeof(newrow),"\n%s,%s,%s,%s",id,name,email,role);

    FILE *fp=fopen("database.csv","a");
    if(fp==NULL){
        printf("Error opening database.\n");
    }
    else{
        fputs(newrow,fp);
        printf("record added successfully\n");
    }

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete(const char *target_id) {
    FILE *fp = fopen("database.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
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
            continue;
        }

        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("database.csv");
    rename("temp.csv", "database.csv");

    if (found)
        printf("Row with ID %s deleted successfully.\n", target_id);
    else
        printf("No record found with ID: %s\n", target_id);
}







int main(){ 
    printf("\t\t Welcome To The Database Management System\n");
    
    int choise;
    char id[20];
    printf("Press 1 to search a record\n");
    printf("Press 2 to add a new record\n");
    printf("Press 3 to delete an existing record\n");
    scanf("%d",&choise);

    switch (choise){
    case 1:
        
        printf("Enter the id of the record you want to search\n");
        getchar();
        fgets(id,sizeof(id),stdin);
        id[strcspn(id, "\n")] = '\0'; 
        search(id);
        break;

    case 2:
        int on=1;
        while(on){
        getchar();
        add();
        printf("Press 1 to enter another record and 0 to exit the system\n");
        scanf("%d",&on);
        }
        break;

    case 3:
        printf("Enter the id of the record you want to delete\n");
        getchar();
        fgets(id,sizeof(id),stdin);
        id[strcspn(id, "\n")] = '\0'; 
        delete(id);
        break;   

    
    default:
        printf("Invalid choise\n");
        printf("run Again\n");
        break;
    }
}




