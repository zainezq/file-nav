#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

// Function prototype
int getDir(char *dir);
int makeFile(FILE *file);


int main(){
    FILE *fptr;
    char cwd[FILENAME_MAX]; //4096
    int choice;
    while (1)
    {
        printf("1. Display current directory\n");
        printf("2. Make a new file\n");
        printf("3. Exit\n");
        // Get user input
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                getDir(cwd);
                break;
            case 2:
                makeFile(fptr);
            case 3:
                printf("Exiting program\n");
                return 0;
        }
        
        
   
    }
    
    return 0;
}

    int getDir(char *dir){
        if (getcwd(dir, FILENAME_MAX) != NULL) {
       printf("Current working dir: %s\n", dir);
        } else {
       perror("getcwd() error");
       return 1;
        }
        return 0;
    }

    int makeFile(FILE *file){
        file = fopen("filename.txt", "w");
        fclose(file);
        return 0;
    }