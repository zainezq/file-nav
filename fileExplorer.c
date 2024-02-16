#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// ANSI color escape codes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Function prototype
int getDir(char *dir);
int makeFile(FILE *file);
void ls();
int strcmp();
void removeFile();
void displayChoice();
void routedPrompt();
void clearInputBuffer();
void displayContent();


void displayChoice() {
    printf(ANSI_COLOR_GREEN "These are the options:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "1. Display current directory\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "2. Make a new file\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "3. List all files\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "4. Remove a file\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "5. Display a file\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "6. Exit\n" ANSI_COLOR_RESET);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main(){
    FILE *fptr;
    char cwd[FILENAME_MAX]; //4096
    int choice;
        displayChoice();
        printf("Enter your choice: ");
        
    while (1)
    {
        scanf("%d", &choice);
clearInputBuffer(); // Clear the input buffer after reading the integer
        switch (choice){
            case 1:
                printf("\n");
                getDir(cwd);
                printf("\n");
                break;
            case 2:
                printf("\n");
                makeFile(fptr);
                printf("\n");
                break;
            case 3:
                printf("\n");
                ls();
                printf("\n");
                break;
            case 4:
                printf("\n");
                removeFile();
                printf("\n");
                break;
            case 5:
                printf("\n");
                displayContent();
                printf("\n");
                break;
            case 6:
                printf("Exiting program\n");
                return 0;
        }
        
        // After executing a command, prompt the user to exit or go back to the main function
        printf("Do you want to exit the program? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
        clearInputBuffer();

        if (choice == 1) {
            printf("Exiting program\n");
            return 0;
        } else {
            displayChoice();
            printf("Enter your choice: ");
        }
    }

    return 0;
}

    int getDir(char *dir){
        if (getcwd(dir, FILENAME_MAX) != NULL) {
       printf("Current working dir: \033[1;34m%s\033[0m\n", dir);
        } else {
       perror("getcwd() error");
       return 1;
        }
        return 0;
    }

    int makeFile(FILE *file){
        char fileName[100];
        printf("Enter a name for the file: ");
        scanf("%99s", fileName);
        file = fopen(fileName, "w");

        if (file == NULL) {
            printf("Error creating the file.\n");
            return 1; // Exit the program with an error code
        }

        fclose(file);
        printf("File '%s' created successfully.\n", fileName);
        printf("\n");
        displayChoice();
        return 0;
    }

    void removeFile(){
    DIR *directory;
    struct dirent *entry;

    // Open the directory
    directory = opendir(".");

    // Check if the directory was successfully opened
    if (directory == NULL) {
        perror("Unable to open directory");
        return;
    }

    // Arrays to store folder and file names
    char **folders = NULL;
    char **files = NULL;
    int folderCount = 0;
    int fileCount = 0;


    // Read directory entries
    while ((entry = readdir(directory)) != NULL) {
        // Ignore '.' and '..' entries
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Allocate memory for the entry name
            char *name = malloc(strlen(entry->d_name) + 1);
            strcpy(name, entry->d_name);

            // Check if it's a directory or a regular file
            if (entry->d_type == DT_DIR) {
                folders = realloc(folders, (folderCount + 1) * sizeof(char *));
                folders[folderCount++] = name;
            } else if (entry->d_type == DT_REG) {
                files = realloc(files, (fileCount + 1) * sizeof(char *));
                files[fileCount++] = name;
            }
        }
    }

    // Close the directory
    closedir(directory);

    // Display the list of files
    printf(ANSI_COLOR_GREEN"Files in the current directory:\n"ANSI_COLOR_RESET);
    for (int i = 0; i < fileCount; i++) {
        printf(ANSI_COLOR_YELLOW" %d. %s\n"ANSI_COLOR_RESET, i + 1, files[i]);
    }

    // Prompt the user to choose a file to delete
    if (fileCount > 0) {
        int choice;
        printf("Enter the number of the file to delete (0 to cancel): ");
        scanf("%d", &choice);

        if (choice > 0 && choice <= fileCount) {
            // Delete the selected file
            remove(files[choice - 1]);
            printf("File '%s' has been deleted.\n", files[choice - 1]);
        } else {
            printf("Deletion canceled.\n");
        }
    } else {
        printf("No files to delete.\n");
    }

    // Free allocated memory
    for (int i = 0; i < folderCount; i++) {
        free(folders[i]);
    }
    free(folders);

    for (int i = 0; i < fileCount; i++) {
        free(files[i]);
    }
    free(files);
}

    void ls(){
    DIR *directory;
    struct dirent *entry;

    // Open the directory
    directory = opendir(".");

    // Check if the directory was successfully opened
    if (directory == NULL) {
        perror("Unable to open directory");
        return;
    }

    // Arrays to store folder and file names
    char **folders = NULL;
    char **files = NULL;
    int folderCount = 0;
    int fileCount = 0;

    // Read directory entries
    while ((entry = readdir(directory)) != NULL) {
        // Skip entries for "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get the full path of the entry
        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", ".", entry->d_name);

        // Get information about the entry
        struct stat statbuf;
        if (stat(fullpath, &statbuf) == -1) {
            perror("Unable to get file status");
            continue;
        }

        // Collect folder and file names
        if (S_ISDIR(statbuf.st_mode)) {
            // Directory
            folders = realloc(folders, (folderCount + 1) * sizeof(char *));
            folders[folderCount] = strdup(entry->d_name);
            folderCount++;
        } else {
            // File
            files = realloc(files, (fileCount + 1) * sizeof(char *));
            files[fileCount] = strdup(entry->d_name);
            fileCount++;
        }

    }

        // Close the directory
        closedir(directory);

        // Print folders
        for (int i = 0; i < folderCount; i++) {
            printf("\033[1;34m%s\033[0m   ", folders[i]);
            free(folders[i]);
        }
        free(folders);

        // Print files
        for (int i = 0; i < fileCount; i++) {
            printf("\033[1;32m%s\033[0m   ", files[i]);
            free(files[i]);
        }
        free(files);

        printf("\n");

    }   

    void displayContent(){
    DIR *directory;
    struct dirent *entry;

    // Open the directory
    directory = opendir(".");

    // Check if the directory was successfully opened
    if (directory == NULL) {
        perror("Unable to open directory");
        return;
    }

    // Arrays to store folder and file names
    char **folders = NULL;
    char **files = NULL;
    int folderCount = 0;
    int fileCount = 0;


    // Read directory entries
    while ((entry = readdir(directory)) != NULL) {
        // Ignore '.' and '..' entries
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Allocate memory for the entry name
            char *name = malloc(strlen(entry->d_name) + 1);
            strcpy(name, entry->d_name);

            // Check if it's a directory or a regular file
            if (entry->d_type == DT_DIR) {
                folders = realloc(folders, (folderCount + 1) * sizeof(char *));
                folders[folderCount++] = name;
            } else if (entry->d_type == DT_REG) {
                files = realloc(files, (fileCount + 1) * sizeof(char *));
                files[fileCount++] = name;
            }
        }
    }

    // Close the directory
    closedir(directory);

    // Display the list of files
    printf(ANSI_COLOR_GREEN"Files in the current directory:\n"ANSI_COLOR_RESET);
    for (int i = 0; i < fileCount; i++) {
        printf(ANSI_COLOR_YELLOW" %d. %s\n"ANSI_COLOR_RESET, i + 1, files[i]);
    }

    // Prompt the user to choose a file to display
    if (fileCount > 0) {
        int choice;
        printf("Enter the number of the file to display (0 to cancel): ");
        scanf("%d", &choice);


        if (choice > 0 && choice <= fileCount) {
            // display the selected file
            FILE *selectedFile = fopen(files[choice - 1], "r");
            if (selectedFile == NULL) {
                perror("Unable to open file");
            } else {
                // Read and display the content of the file
                char ch;
                printf("Content of the selected file:\n");
                while ((ch = fgetc(selectedFile)) != EOF) {
                    putchar(ch);
                }
                fclose(selectedFile);
            }
        } else {
            printf("Displaying canceled.\n");
        }
    } else {
        printf("No files to display.\n");
    }

    // Free allocated memory
    for (int i = 0; i < folderCount; i++) {
        free(folders[i]);
    }
    free(folders);

    for (int i = 0; i < fileCount; i++) {
        free(files[i]);
    }
    free(files);
    }




