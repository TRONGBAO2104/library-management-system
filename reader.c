#include "reader.h"

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
    readerID[*readerCount] = *readerCount + 1;

    printf("Name: ");
    fgets(readerName[*readerCount], MAX_STRING, stdin);
    readerName[*readerCount][strcspn(readerName[*readerCount], "\n")] = 0;

    printf("CMND: ");
    scanf("%s", readerCMND[*readerCount]);
    clearInputBuffer();

    printf("Birth Date (YYYY-MM-DD): ");
    scanf("%s", readerBirthDate[*readerCount]);
    clearInputBuffer();

    printf("Gender (Male/Female): ");
    scanf("%s", readerGender[*readerCount]);
    clearInputBuffer();

    printf("Email: ");
    scanf("%s", readerEmail[*readerCount]);
    clearInputBuffer();

    printf("Phone: ");
    scanf("%s", readerPhone[*readerCount]);
    clearInputBuffer();

    printf("Address: ");
    fgets(readerAddress[*readerCount], MAX_STRING, stdin);
    readerAddress[*readerCount][strcspn(readerAddress[*readerCount], "\n")] = 0;

    // Set card issue date to current time
    readerCardIssueDate[*readerCount] = time(NULL);
    
    // Set expiry date to 48 months from issue date
    readerCardExpiryDate[*readerCount] = readerCardIssueDate[*readerCount] + (48 * 30 * 24 * 60 * 60);

    readerMembershipYear[*readerCount] = time(NULL) / (365 * 24 * 60 * 60) + 1970;
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
    if (strlen(name) > 0) strcpy(readerName[index], name);

    printf("Enter new email (or press Enter to keep current): ");
    char email[MAX_STRING];
    fgets(email, MAX_STRING, stdin);
    email[strcspn(email, "\n")] = 0;
    if (strlen(email) > 0) strcpy(readerEmail[index], email);

    printf("Enter new phone (or press Enter to keep current): ");
    char phone[MAX_STRING];
    fgets(phone, MAX_STRING, stdin);
    phone[strcspn(phone, "\n")] = 0;
    if (strlen(phone) > 0) strcpy(readerPhone[index], phone);

    printf("Enter new address (or press Enter to keep current): ");
    char address[MAX_STRING];
    fgets(address, MAX_STRING, stdin);
    address[strcspn(address, "\n")] = 0;
    if (strlen(address) > 0) strcpy(readerAddress[index], address);

    printf("Enter new membership year (or 0 to keep current): ");
    int year;
    scanf("%d", &year);
    clearInputBuffer();
    if (year > 0) readerMembershipYear[index] = year;

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
        readerID[i] = readerID[i + 1];
        strcpy(readerName[i], readerName[i + 1]);
        strcpy(readerEmail[i], readerEmail[i + 1]);
        strcpy(readerPhone[i], readerPhone[i + 1]);
        strcpy(readerAddress[i], readerAddress[i + 1]);
        readerMembershipYear[i] = readerMembershipYear[i + 1];
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
        if (strstr(readerName[i], searchTerm) || strstr(readerEmail[i], searchTerm)) {
            printf("ID: %d\n", readerID[i]);
            printf("Name: %s\n", readerName[i]);
            printf("Email: %s\n", readerEmail[i]);
            printf("Phone: %s\n", readerPhone[i]);
            printf("Address: %s\n", readerAddress[i]);
            printf("Membership Year: %d\n", readerMembershipYear[i]);
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
        printf("ID: %d\n", readerID[i]);
        printf("Name: %s\n", readerName[i]);
        printf("Email: %s\n", readerEmail[i]);
        printf("Phone: %s\n", readerPhone[i]);
        printf("Address: %s\n", readerAddress[i]);
        printf("Membership Year: %d\n", readerMembershipYear[i]);
        printf("----------------------------------------\n");
    }
}

void searchReaderByCMND(int readerCount) {
    char cmnd[MAX_STRING];
    printf("Enter CMND to search: ");
    scanf("%s", cmnd);
    clearInputBuffer();

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < readerCount; i++) {
        if (strcmp(readerPhone[i], cmnd) == 0) {
            printf("ID: %d\n", readerID[i]);
            printf("Name: %s\n", readerName[i]);
            printf("Email: %s\n", readerEmail[i]);
            printf("Phone: %s\n", readerPhone[i]);
            printf("Address: %s\n", readerAddress[i]);
            printf("Membership Year: %d\n", readerMembershipYear[i]);
            printf("----------------------------------------\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No reader found with this CMND.\n");
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
    char searchName[MAX_STRING];
    printf("Enter reader name to search: ");
    fgets(searchName, MAX_STRING, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;

    for (int i = 0; i < borrowingCount; i++) {
        if (strstr(readerName[borrowingReaderID[i]], searchName)) {
            printf("\nReader: %s (CMND: %s)\n", readerName[borrowingReaderID[i]], readerCMND[borrowingReaderID[i]]);
            printf("Borrowed Books:\n");
            for (int j = 0; j < borrowingBookCount[i]; j++) {
                int bookIndex = findBookByISBN(MAX_BOOKS, borrowingBooks[i][j]);
                if (bookIndex != -1) {
                    printf("- %s (ISBN: %s)\n", bookTitle[bookIndex], bookISBN[bookIndex]);
                }
            }
            printf("Borrow Date: %s", ctime(&borrowingDate[i]));
            printf("Due Date: %s", ctime(&dueDate[i]));
            if (isReturned[i]) {
                printf("Return Date: %s", ctime(&returnDate[i]));
            }
            printf("----------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found borrowed by readers with this name.\n");
    }
} 