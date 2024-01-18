#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

void listDirectoryContents(const char *path) {
    DIR *directory;
    struct dirent *entry;

    // Open the directory
    directory = opendir(path);

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
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

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

int main(int argc, char *argv[]) {
    // Check if a directory path is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    // List the contents of the specified directory
    listDirectoryContents(argv[1]);

    return 0;
}
