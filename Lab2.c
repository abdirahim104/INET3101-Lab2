/*
 * Lab 2: Memory and Structures
 * 
 * Author: Abdirahim Abdullahi
 * 
 * Description:
 * This program simulates an in-memory "database" of part records. Each record is
 * represented by a struct containing several fields (part number, part name, size,
 * metric, and cost). The database grows or shrinks dynamically using malloc and
 * realloc calls as we add or remove records. No static arrays or linked lists
 * are used.
 * 
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
// Define the struct for each record in our "database"
typedef struct {
    int partNumber;       // e.g. 394892948
    char partName[50];    // e.g. "Poly pipe"
    float partSize;       // e.g. 23.75
    char sizeMetric[10];  // e.g. "mm"
    float partCost;       // e.g. 8.83
} PartRecord;

// Function declarations
void PrintAllRecords(const PartRecord* db, int count);
void PrintNumRecords(int count);
void PrintDatabaseSize(int count);
void AddRecord(PartRecord** db, int* count);
void DeleteRecord(PartRecord** db, int* count);

int main(void) {
    // database will point to a block of memory that stores our PartRecord array
    PartRecord* database = NULL;
    // track how many records we have at any moment
    int recordCount = 0;
    int choice;

    do {
        // Print our menu
        printf("\n===== MENU =====\n");
        printf("1) Print all records\n");
        printf("2) Print number of records\n");
        printf("3) Print database size (in bytes)\n");
        printf("4) Add a record\n");
        printf("5) Delete the last record\n");
        printf("6) Exit\n");
        printf("Select an option: ");

        // Validate user's menu choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // clear the buffer
            continue;
        }

        switch (choice) {
            case 1:
                PrintAllRecords(database, recordCount);
                break;
            case 2:
                PrintNumRecords(recordCount);
                break;
            case 3:
                PrintDatabaseSize(recordCount);
                break;
            case 4:
                AddRecord(&database, &recordCount);
                break;
            case 5:
                DeleteRecord(&database, &recordCount);
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (choice != 6);

    // free any leftover memory before finishing
    free(database);
    return 0;
}

// Prints every record currently stored in the database
void PrintAllRecords(const PartRecord* db, int count) {
    if (count == 0) {
        printf("\nNo records stored yet.\n");
        return;
    }
    printf("\n--- All Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nRecord #%d\n", i + 1);
        printf(" Part number:     %d\n", db[i].partNumber);
        printf(" Part name:       %s\n", db[i].partName);
        printf(" Part size:       %.2f\n", db[i].partSize);
        printf(" Size metric:     %s\n", db[i].sizeMetric);
        printf(" Part cost:       $%.2f\n", db[i].partCost);
    }
}

// Prints how many records are in the database
void PrintNumRecords(int count) {
    printf("\nNumber of records: %d\n", count);
}

// Calculates how many total bytes are allocated for the database
void PrintDatabaseSize(int count) {
    // each PartRecord is sizeof(PartRecord) bytes in memory
    printf("\nDatabase size: %lu bytes\n", (unsigned long)(count * sizeof(PartRecord)));
}

// Adds a new record, reallocating memory to increase the array size by 1
void AddRecord(PartRecord** db, int* count) {
    int newCount = *count + 1;

    // request more memory to hold the extra record
    PartRecord* temp = realloc(*db, newCount * sizeof(PartRecord));
    if (temp == NULL) {
        printf("\nMemory reallocation failed. Cannot add a new record.\n");
        return;
    }

    // update the pointer to the newly allocated block and the record count
    *db = temp;
    *count = newCount;

    // reference the newly added record (last position in the array)
    PartRecord* newRecord = &((*db)[newCount - 1]);

    // clear any leftover newline so we can use fgets properly
    while (getchar() != '\n');

    printf("\n--- Add a New Record ---\n");
    printf("Enter part number (integer): ");
    scanf("%d", &newRecord->partNumber);

    while (getchar() != '\n');

    printf("Enter part name (up to 49 chars): ");
    fgets(newRecord->partName, sizeof(newRecord->partName), stdin);
    // remove newline char if it's at the end
    size_t len = strlen(newRecord->partName);
    if (len > 0 && newRecord->partName[len - 1] == '\n') {
        newRecord->partName[len - 1] = '\0';
    }

    printf("Enter part size (float): ");
    scanf("%f", &newRecord->partSize);

    while (getchar() != '\n');

    printf("Enter size metric (up to 9 chars): ");
    fgets(newRecord->sizeMetric, sizeof(newRecord->sizeMetric), stdin);
    len = strlen(newRecord->sizeMetric);
    if (len > 0 && newRecord->sizeMetric[len - 1] == '\n') {
        newRecord->sizeMetric[len - 1] = '\0';
    }

    printf("Enter part cost (float): ");
    scanf("%f", &newRecord->partCost);

    printf("\nA new record was successfully added.\n");
}

// Deletes the last record from the database, shrinking the memory allocation
void DeleteRecord(PartRecord** db, int* count) {
    if (*count == 0) {
        printf("\nThere are no records to delete.\n");
        return;
    }

    int newCount = *count - 1;

    if (newCount == 0) {
        // if this was our only record, just free everything
        free(*db);
        *db = NULL;
        *count = 0;
        printf("\nDeleted the last record. The database is now empty.\n");
        return;
    }

    // otherwise, shrink our memory block
    PartRecord* temp = realloc(*db, newCount * sizeof(PartRecord));
    if (temp == NULL) {
        // if something fails during shrink, keep old data 
        printf("\nError: reallocation failed while deleting.\n");
        return;
    }

    *db = temp;
    *count = newCount;
    printf("\nDeleted the last record. New record count: %d\n", *count);
}