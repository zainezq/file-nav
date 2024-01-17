#include <stdio.h>

int main() {
    int choice;

    while (1) {
        // Display menu or options to the user
        printf("1. Perform Task 1\n");
        printf("2. Perform Task 2\n");
        printf("3. Exit\n");

        // Get user input
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Process user input
        switch (choice) {
            case 1:
                // Code for Task 1
                printf("Performing Task 1\n");
                break;

            case 2:
                // Code for Task 2
                printf("Performing Task 2\n");
                break;

            case 3:
                // Exit the program
                printf("Exiting program\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }

        // Optionally, you can clear the input buffer
        while (getchar() != '\n');
    }

    return 0;
}
