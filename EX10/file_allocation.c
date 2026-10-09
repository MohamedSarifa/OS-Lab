#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_FILES 50

struct File {
    char name[20];
    int start;
    int length;
};

struct File directory[MAX_FILES];
int freelist[MAX_BLOCKS];
int nblocks;
int fileCount = 0;

void allocateFile() {
    char name[20];
    int length;
    int i, j;
    int start = -1;
    int count = 0;

    printf("\nEnter file name: ");
    scanf("%s", name);
    printf("Enter file length: ");
    scanf("%d", &length);

    /* Validate file length */
    if (length <= 0) {
        printf("\nInvalid file length.\n");
        return;
    }

    /* Check if file already exists in directory */
    for (i = 0; i < fileCount; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            printf("\nFile '%s' already exists.\n", name);
            return;
        }
    }

    /* Find consecutive free blocks automatically (First Fit) */
    for (i = 0; i < nblocks; i++) {
        if (freelist[i] == 0) {
            count++;
            if (count == length) {
                start = i - length + 1;
                break;
            }
        } else {
            count = 0; // Sequence is broken
        }
    }

    /* If no adequate contiguous blocks are found */
    if (start == -1) {
        printf("\nFile cannot be allocated.\n");
        printf("Required %d consecutive blocks are not available.\n", length);
        return;
    }

    /* Allocate blocks and save metadata */
    for (j = start; j < start + length; j++) {
        freelist[j] = 1;
    }

    strcpy(directory[fileCount].name, name);
    directory[fileCount].start = start;
    directory[fileCount].length = length;
    fileCount++;

    printf("\nFile allocated successfully.\n");
    printf("Assigned Starting Block: %d\n", start);
    printf("Allocated Blocks: ");
    for (j = start; j < start + length; j++) {
        printf("%d ", j);
    }
    printf("\n");
}

void displayDirectory() {
    int i;
    if (fileCount == 0) {
        printf("\nDirectory is empty.\n");
        return;
    }
    printf("\n=====================================\n");
    printf("            FILE DIRECTORY           \n");
    printf("=====================================\n");
    printf("%-15s %-10s %-10s\n", "File", "Start", "Length");
    printf("-------------------------------------\n");
    for (i = 0; i < fileCount; i++) {
        printf("%-15s %-10d %-10d\n", directory[i].name, directory[i].start, directory[i].length);
    }
    printf("-------------------------------------\n");
}

void displayBlocks() {
    int i;
    int freeCount = 0;
    printf("\nBlock Status\n");
    printf("-------------------------------\n");
    for (i = 0; i < nblocks; i++) {
        printf("Block %2d : ", i);
        if (freelist[i] == 0) {
            printf("Free\n");
            freeCount++;
        } else {
            printf("Allocated\n");
        }
    }
    printf("-------------------------------\n");
    printf("Total Blocks: %d | Free: %d | Allocated: %d\n", nblocks, freeCount, nblocks - freeCount);
}

void deleteFile() {
    char name[20];
    int i, j;
    int found = -1;

    printf("\nEnter file name to delete: ");
    scanf("%s", name);

    for (i = 0; i < fileCount; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nFile '%s' not found.\n", name);
        return;
    }

    /* Free the occupied blocks */
    for (j = directory[found].start; j < directory[found].start + directory[found].length; j++) {
        freelist[j] = 0;
    }

    /* Shift directory items down to clear slot */
    for (i = found; i < fileCount - 1; i++) {
        directory[i] = directory[i + 1];
    }
    fileCount--;

    printf("\nFile '%s' deleted successfully.\n", name);
}

void searchFile() {
    char name[20];
    int i, j;

    printf("\nEnter file name to search: ");
    scanf("%s", name);

    for (i = 0; i < fileCount; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            printf("\nFile found details:\n");
            printf("-------------------------------\n");
            printf("File Name: %s\n", directory[i].name);
            printf("Starting Block: %d\n", directory[i].start);
            printf("Length (Blocks): %d\n", directory[i].length);
            printf("Occupied Blocks: ");
            for (j = directory[i].start; j < directory[i].start + directory[i].length; j++) {
                printf("%d ", j);
            }
            printf("\n-------------------------------\n");
            return;
        }
    }
    printf("\nFile '%s' not found in the directory.\n", name);
}

int main() {
    int choice;
    int i;

    printf("========================================\n");
    printf("      CONTIGUOUS FILE ALLOCATION        \n");
    printf("========================================\n");

    printf("\nEnter number of blocks: ");
    scanf("%d", &nblocks);

    if (nblocks <= 0 || nblocks > MAX_BLOCKS) {
        printf("Invalid number of blocks.\n");
        return 0;
    }

    /* Pre-initialize initial block allocation status */
    printf("\nEnter block status setup:\n");
    printf("0 - Free\n");
    printf("1 - Allocated\n\n");
    for (i = 0; i < nblocks; i++) {
        printf("Block %d: ", i);
        scanf("%d", &freelist[i]);
        if (freelist[i] != 0 && freelist[i] != 1) {
            printf("Invalid status! Enter only 0 or 1.\n");
            return 0;
        }
    }

    while (1) {
        printf("\n1. Allocate File");
        printf("\n2. Display Directory");
        printf("\n3. Display Blocks");
        printf("\n4. Delete File");
        printf("\n5. Search File");
        printf("\n6. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                allocateFile();
                break;
            case 2:
                displayDirectory();
                break;
            case 3:
                displayBlocks();
                break;
            case 4:
                deleteFile();
                break;
            case 5:
                searchFile();
                break;
            case 6:
                printf("\nProgram terminated.\n");
                return 0;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
    return 0;
}
