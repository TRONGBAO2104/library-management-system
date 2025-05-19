#include "reader.h"
#include "book.h"
#include "borrowing.h"
#include "library.h"

// Define the array of readers
Reader readers[MAX_READERS];

/**
 * @brief Add a new reader
 * @param readerCount Pointer to the current number of readers
 * @return void
 * 
 * The user can enter reader details and adds that reader to the library (ensures all required fields are filled)
 * It checks for maximum capacity and duplicate IDs.
 */
void addReader(int *readerCount) {
    if (*readerCount >= MAX_READERS) {
        printf("Maximum number of readers reached!\n");
        return;
    }

    printf("\nEnter Reader Information:\n");
    printf("ID: %d\n", *readerCount + 1);
    readers[*readerCount].ID = *readerCount + 1;

    printf("Name: ");
    fgets(readers[*readerCount].name, MAX_STRING, stdin);
    readers[*readerCount].name[strcspn(readers[*readerCount].name, "\n")] = 0;

    printf("CMND: ");
    scanf("%s", readers[*readerCount].CMND);
    clearInputBuffer();

    printf("Birth Date (YYYY-MM-DD): ");
    scanf("%s", readers[*readerCount].birthDate);
    clearInputBuffer();

    printf("Gender (Male/Female): ");
    scanf("%s", readers[*readerCount].gender);
    clearInputBuffer();

    printf("Email: ");
    scanf("%s", readers[*readerCount].email);
    clearInputBuffer();

    printf("Phone: ");
    scanf("%s", readers[*readerCount].phone);
    clearInputBuffer();

    printf("Address: ");
    fgets(readers[*readerCount].address, MAX_STRING, stdin);
    readers[*readerCount].address[strcspn(readers[*readerCount].address, "\n")] = 0;

    // Set card issue date to current time
    readers[*readerCount].cardIssueDate = time(NULL);
    
    // Set expiry date to 48 months from issue date
    readers[*readerCount].cardExpiryDate = readers[*readerCount].cardIssueDate + (48 * 30 * 24 * 60 * 60);

    readers[*readerCount].membershipYear = time(NULL) / (365 * 24 * 60 * 60) + 1970;
    (*readerCount)++;
    printf("Reader added successfully!\n");
}

/**
 * @brief Update reader's information
 * @param readerCount Current number of readers in the system
 * @return void
 * 
 * Update any field (press "Enter" to keep the current value of a field.
 */
void updateReader(int readerCount) {
    int id;
    printf("Enter reader ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = findReaderByID(readerCount, id);
    if (index == -1) {
        printf("Reader not found!\n");
        return;
    }

    printf("Enter new name (or press Enter to keep current): ");
    char name[MAX_STRING];
    fgets(name, MAX_STRING, stdin);
    name[strcspn(name, "\n")] = 0;
    if (strlen(name) > 0) strcpy(readers[index].name, name);

    printf("Enter new email (or press Enter to keep current): ");
    char email[MAX_STRING];
    fgets(email, MAX_STRING, stdin);
    email[strcspn(email, "\n")] = 0;
    if (strlen(email) > 0) strcpy(readers[index].email, email);

    printf("Enter new phone (or press Enter to keep current): ");
    char phone[MAX_STRING];
    fgets(phone, MAX_STRING, stdin);
    phone[strcspn(phone, "\n")] = 0;
    if (strlen(phone) > 0) strcpy(readers[index].phone, phone);

    printf("Enter new address (or press Enter to keep current): ");
    char address[MAX_STRING];
    fgets(address, MAX_STRING, stdin);
    address[strcspn(address, "\n")] = 0;
    if (strlen(address) > 0) strcpy(readers[index].address, address);

    printf("Enter new membership year (or 0 to keep current): ");
    int year;
    scanf("%d", &year);
    clearInputBuffer();
    if (year > 0) readers[index].membershipYear = year;

    printf("Reader updated successfully!\n");
}

/**
 * @brief Removes a reader
 * @param readerCount Pointer to the current number of readers
 * @return void
 * 
 * Removes a reader by ID and shifts all subsequent readers to maintain array continuity.
 */
void deleteReader(int *readerCount) {
    int id;
    printf("Enter reader ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = findReaderByID(*readerCount, id);
    if (index == -1) {
        printf("Reader not found!\n");
        return;
    }

    // Shift remaining readers
    for (int i = index; i < *readerCount - 1; i++) {
        readers[i] = readers[i + 1];
    }
    (*readerCount)--;
    printf("Reader deleted successfully!\n");
}

/**
 * @brief Searches for readers by name or email
 * @param readerCount Current number of readers in the system
 * @return void
 * 
 * This function displays all readers that match the search term in either their name or email field.
 */
void searchReader(int readerCount) {
    char searchTerm[MAX_STRING];
    printf("Enter search term (name or email): ");
    fgets(searchTerm, MAX_STRING, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < readerCount; i++) {
        if (strstr(readers[i].name, searchTerm) || strstr(readers[i].email, searchTerm)) {
            printf("ID: %d\n", readers[i].ID);
            printf("Name: %s\n", readers[i].name);
            printf("Email: %s\n", readers[i].email);
            printf("Phone: %s\n", readers[i].phone);
            printf("Address: %s\n", readers[i].address);
            printf("Membership Year: %d\n", readers[i].membershipYear);
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No readers found matching the search term.\n");
    }
}

/**
 * @brief Displays all readers in the library system
 * @param readerCount Current number of readers in the system
 * @return void
 * 
 * This function shows detailed information about all readers
 * currently registered in the system.
 */
void displayAllReaders(int readerCount) {
    if (readerCount == 0) {
        printf("No readers registered.\n");
        return;
    }

    printf("\nAll Readers:\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < readerCount; i++) {
        printf("ID: %d\n", readers[i].ID);
        printf("Name: %s\n", readers[i].name);
        printf("Email: %s\n", readers[i].email);
        printf("Phone: %s\n", readers[i].phone);
        printf("Address: %s\n", readers[i].address);
        printf("Membership Year: %d\n", readers[i].membershipYear);
        printf("----------------------------------------\n");
    }
}

void searchReaderByCMND(int readerCount) {
    char searchTerm[MAX_STRING];
    printf("Enter CMND to search: ");
    scanf("%s", searchTerm);
    clearInputBuffer();

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < readerCount; i++) {
        if (strcmp(readers[i].CMND, searchTerm) == 0) {
            printf("ID: %d\n", readers[i].ID);
            printf("Name: %s\n", readers[i].name);
            printf("CMND: %s\n", readers[i].CMND);
            printf("Email: %s\n", readers[i].email);
            printf("Phone: %s\n", readers[i].phone);
            printf("Address: %s\n", readers[i].address);
            printf("Membership Year: %d\n", readers[i].membershipYear);
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No readers found matching the CMND.\n");
    }
}

/**
 * @brief Searches for books by a reader's name
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function displays all books that are currently by a reader
 * whose name matches the search term.
 */
void searchBooksByReaderName(int borrowingCount) {
    char searchTerm[MAX_STRING];
    printf("Enter reader name to search: ");
    fgets(searchTerm, MAX_STRING, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    int found = 0;
    printf("\n=== Books Borrowed by Reader ===\n");
    for (int i = 0; i < borrowingCount; i++) {
        if (strstr(readers[borrowings[i].readerID].name, searchTerm)) {
            printf("Reader: %s (CMND: %s)\n", readers[borrowings[i].readerID].name, readers[borrowings[i].readerID].CMND);
            printf("Books:\n");
            for (int j = 0; j < borrowings[i].bookCount; j++) {
                int bookIndex = findBookByISBN(MAX_BOOKS, borrowings[i].books[j]);
                if (bookIndex != -1) {
                    printf("- %s (ISBN: %s)\n", books[bookIndex].title, books[bookIndex].ISBN);
                }
            }
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found for this reader.\n");
    }
}

// Update the function to save data to the file
void saveReadersToFile(int readerCount) {
    FILE *file = fopen("readers.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    // Save the number of readers
    fprintf(file, "%d\n", readerCount);
    
    // Save the information of each reader
    for (int i = 0; i < readerCount; i++) {
        fprintf(file, "%d\n", readers[i].ID);
        fprintf(file, "%s\n", readers[i].name);
        fprintf(file, "%s\n", readers[i].CMND);
        fprintf(file, "%s\n", readers[i].birthDate);
        fprintf(file, "%s\n", readers[i].gender);
        fprintf(file, "%s\n", readers[i].email);
        fprintf(file, "%s\n", readers[i].phone);
        fprintf(file, "%s\n", readers[i].address);
        fprintf(file, "%ld\n", readers[i].cardIssueDate);
        fprintf(file, "%ld\n", readers[i].cardExpiryDate);
        fprintf(file, "%d\n", readers[i].membershipYear);
    }
    
    fclose(file);
    printf("Readers saved to file successfully.\n");
}

// Update the function to load data from the file
void loadReadersFromFile(int *readerCount) {
    FILE *file = fopen("readers.txt", "r");
    if (file == NULL) {
        printf("No existing reader data found.\n");
        return;
    }
    
    // Read the number of readers
    fscanf(file, "%d\n", readerCount);
    
    // Read the information of each reader
    for (int i = 0; i < *readerCount; i++) {
        fscanf(file, "%d\n", &readers[i].ID);
        
        fgets(readers[i].name, MAX_STRING, file);
        readers[i].name[strcspn(readers[i].name, "\n")] = 0;
        
        fgets(readers[i].CMND, MAX_STRING, file);
        readers[i].CMND[strcspn(readers[i].CMND, "\n")] = 0;
        
        fgets(readers[i].birthDate, MAX_STRING, file);
        readers[i].birthDate[strcspn(readers[i].birthDate, "\n")] = 0;
        
        fgets(readers[i].gender, MAX_STRING, file);
        readers[i].gender[strcspn(readers[i].gender, "\n")] = 0;
        
        fgets(readers[i].email, MAX_STRING, file);
        readers[i].email[strcspn(readers[i].email, "\n")] = 0;
        
        fgets(readers[i].phone, MAX_STRING, file);
        readers[i].phone[strcspn(readers[i].phone, "\n")] = 0;
        
        fgets(readers[i].address, MAX_STRING, file);
        readers[i].address[strcspn(readers[i].address, "\n")] = 0;
        
        fscanf(file, "%ld\n", &readers[i].cardIssueDate);
        fscanf(file, "%ld\n", &readers[i].cardExpiryDate);
        fscanf(file, "%d\n", &readers[i].membershipYear);
    }
    
    fclose(file);
    printf("Readers loaded from file successfully.\n");
}

// Function to find a reader by ID
int findReaderByID(int readerCount, int id) {
    for (int i = 0; i < readerCount; i++) {
        if (readers[i].ID == id) {
            return i;
        }
    }
    return -1;
} 