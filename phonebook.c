#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_contacts(char** name, char** contacts, int max_contacts, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file '%s'\n", filename);
        return 0;
    }

    int num_contacts = 0;
    while (num_contacts < max_contacts && !feof(fp)) {
        if (fscanf(fp, "%24s %11s", name[num_contacts], contacts[num_contacts]) == 2) {
            num_contacts++;
        }
    }

    fclose(fp);
    return num_contacts;
}

void write_contacts(char** name, char** contacts, int num_contacts, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file '%s'\n", filename);
        return;
    }

    for (int i = 0; i < num_contacts; i++) {
        fprintf(fp, "%s %s\n", name[i], contacts[i]);
    }

    fclose(fp);
}

int main() {
    char** name = malloc(sizeof(char*) * 10);
    char** contacts = malloc(sizeof(char*) * 10);

    for (int i = 0; i < 10; i++) {
        name[i] = malloc(sizeof(char) * 25);
        contacts[i] = malloc(sizeof(char) * 12);
    }

    int num_contacts = 0;
    int choice = 0;

    num_contacts = read_contacts(name, contacts, 10, "contacts.txt");

    do {
        printf("\nMenu:\n");
        printf("1. Add contact\n");
        printf("2. Display contacts\n");
        printf("3. Save contacts\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (num_contacts >= 10) {
                    printf("Maximum number of contacts reached.\n");
                } else {
                    printf("\nEnter name: ");
                    scanf("%24s", name[num_contacts]);

                    printf("Enter contact information: ");
                    scanf("%11s", contacts[num_contacts]);

                    num_contacts++;
                }
                break;
            case 2:
                printf("\nContacts:\n");
                for (int i = 0; i < num_contacts; i++) {
                    printf("%s: %s\n", name[i], contacts[i]);
                }
                break;
            case 3:
                write_contacts(name, contacts, num_contacts, "contacts.txt");
                printf("Contacts saved to file 'contacts.txt'\n");
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    for (int i = 0; i < 10; i++) {
        free(name[i]);
        free(contacts[i]);
    }

    free(name);
    free(contacts);

    return 0;
}
