#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILENAME "save.txt"

char dues[100][50];
int dues_amount[100] = {0};
int number_of_dues = 0;
time_t lastSaveTime = 0;

void save_file() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    time_t t = time(NULL);
    fwrite(&t, sizeof(t), 1, file); 

    for (int i = 0; i < number_of_dues; i++) {
        fprintf(file, "%s: %d\n", dues[i], dues_amount[i]);
    }
    fclose(file);
}

void load_file() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No previous save found.\n");
        return;
    }

    fread(&lastSaveTime, sizeof(lastSaveTime), 1, file);

    char name[50];
    int value;
    while (fscanf(file, "%49[^:]: %d\n", name, &value) == 2) {
        strcpy(dues[number_of_dues], name);
        dues_amount[number_of_dues] = value;
        number_of_dues++;
    }
    fclose(file);
}

void calculate_due() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int current_day = tm_info->tm_mday;
    int current_month = tm_info->tm_mon + 1;
    int current_year = tm_info->tm_year + 1900;

    struct tm *last_tm_info = localtime(&lastSaveTime);
    int last_month = last_tm_info->tm_mon + 1;
    int last_year = last_tm_info->tm_year + 1900;

    int months_passed = (current_year - last_year) * 12 + (current_month - last_month);

    if (current_day >= 21 && months_passed > 0) {
        printf("Updating dues... Adding $2 per month missed.\n");
        for (int i = 0; i < number_of_dues; i++) {
            dues_amount[i] += 2 * months_passed;
        }
    }
}

void add_due() {
    char due_name[50];
    int due_amount;
    printf("Enter due name: ");
    scanf("%s", due_name);
    printf("Enter due amount: ");
    scanf("%d", &due_amount);

    strcpy(dues[number_of_dues], due_name);
    dues_amount[number_of_dues] = due_amount;
    number_of_dues++;
}

void remove_dues() {
    char due_name[50];
    print_dues();
    printf("Enter due name to remove: ");
    scanf("%s", due_name);

    for (int i = 0; i < number_of_dues; i++) {
        if (strcmp(dues[i], due_name) == 0) {
            for (int y = i; y < number_of_dues - 1; y++) {
                strcpy(dues[y], dues[y + 1]);
                dues_amount[y] = dues_amount[y + 1];
            }
            number_of_dues--;
            printf("Due removed successfully.\n");
            return;
        }
    }
    printf("Due not found.\n");
}


void print_dues() {
    if (number_of_dues == 0) {
        printf("No dues recorded.\n");
        return;
    }

    for (int i = 0; i < number_of_dues; i++) {
        printf("%s: $%d\n", dues[i], dues_amount[i]);
    }
}

int main() {
    load_file();
    calculate_due();

    while (1) {
        printf("\n=== Dues Manager ===\n");
        printf("1. Add due\n");
        printf("2. Remove due\n");
        printf("3. Print dues\n");
        printf("4. Save and exit\n");
        printf("Enter your choice: ");
        
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_due();
                break;
            case 2:
                remove_dues();
                break;
            case 3:
                print_dues();
                break;
            case 4:
                save_file();
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
