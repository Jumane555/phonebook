
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This function reads contacts from a file and stores them in the given arrays.
// It returns the number of contacts read.
int read_contacts(char** name, char** contacts, int max_contacts, const char* filename) {
    // Open the file for reading.
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file '%s'\n", filename);
        return 0;
    }

    int num_contacts = 0;
     // Read contacts from the file until we reach the end or the maximum number of contacts.
    while (num_contacts < max_contacts && !feof(fp)) {
    // Use fscanf to read the name and contact information from the file.
        // Each field is limited to a certain number of characters to prevent buffer overflow.
        // If fscanf successfully reads both fields, increment the number of contacts.
        if (fscanf(fp, "%24s %11s", name[num_contacts], contacts[num_contacts]) == 2) {
            num_contacts++;
        }
    }

    fclose(fp);
    return num_contacts;
}

// This function writes contacts from the given arrays to a file.
void write_contacts(char** name, char** contacts, int num_contacts, const char* filename) {
    // Open the file for writing.
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file '%s'\n", filename);
        return;
    }
 // Write each contact
    for (int i = 0; i < num_contacts; i++) {
        fprintf(fp, "%s %s\n", name[i], contacts[i]);
    }

    fclose(fp);
}

int main() {
     // Allocate memory for arrays to hold up to 10 contacts.
    char** name = malloc(sizeof(char*) * 10);
    char** contacts = malloc(sizeof(char*) * 10);
   // Allocate memory for each name and contact information field.
        // Each field is limited to a certain number of characters to prevent buffer overflow.
    for (int i = 0; i < 10; i++) {
        name[i] = malloc(sizeof(char) * 25);
        contacts[i] = malloc(sizeof(char) * 12);
    }

    int num_contacts = 0;
    int choice = 0;

    // Read contacts from the file "contacts.txt".

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
            case 1: // Add a new contact if there is room in the arrays.
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
                 // Display all contacts in the arrays.
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

