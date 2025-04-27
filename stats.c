#include "stats.h"

/**
 * @brief Displays book statistics
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * This function shows various statistics about the books in the library.
 */
void displayBookStatistics(int bookCount) {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    printf("\nBook Statistics:\n");
    printf("----------------------------------------\n");
    printf("Total number of books: %d\n", bookCount);
    float totalValue = 0;
    for (int i = 0; i < bookCount; i++) {
        totalValue += bookPrice[i] * bookQuantity[i];
    }
    printf("Total value of books: %.2f\n", totalValue);
    printf("\nBooks by Category:\n");
    for (int i = 0; i < bookCount; i++) {
        int count = 1;
        for (int j = i + 1; j < bookCount; j++) {
            if (strcmp(bookCategory[i], bookCategory[j]) == 0) {
                count++;
            }
        }
        printf("%s: %d\n", bookCategory[i], count);
    }
    printf("----------------------------------------\n");
}

/**
 * @brief Displays reader statistics
 * @param readerCount Current number of readers in the system
 * @return void
 * 
 * This function shows various statistics about the readers.
 */
void displayReaderStatistics(int readerCount) {
    if (readerCount == 0) {
        printf("No readers registered.\n");
        return;
    }
    printf("\nReader Statistics:\n");
    printf("----------------------------------------\n");
    printf("Total number of readers: %d\n", readerCount);
    printf("\nReaders by Membership Year:\n");
    for (int i = 0; i < readerCount; i++) {
        int count = 1;
        for (int j = i + 1; j < readerCount; j++) {
            if (readerMembershipYear[i] == readerMembershipYear[j]) {
                count++;
            }
        }
        printf("%d: %d\n", readerMembershipYear[i], count);
    }
    printf("----------------------------------------\n");
}

/**
 * @brief Displays statistics about readers by gender
 * @param readerCount Current number of readers
 * @return void
 * 
 * This function shows the distribution of readers by gender.
 */
void displayGenderStatistics(int readerCount) {
    int maleCount = 0;
    int femaleCount = 0;
    for (int i = 0; i < readerCount; i++) {
        if (strcmp(readerGender[i], "Male") == 0) {
            maleCount++;
        } else if (strcmp(readerGender[i], "Female") == 0) {
            femaleCount++;
        }
    }
    printf("\n=== Gender Statistics ===\n");
    printf("Total Readers: %d\n", readerCount);
    printf("Male Readers: %d (%.1f%%)\n", maleCount, (float)maleCount / readerCount * 100);
    printf("Female Readers: %d (%.1f%%)\n", femaleCount, (float)femaleCount / readerCount * 100);
}

/**
 * @brief Displays borrowing statistics
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function shows various statistics about the borrowing activities.
 */
void displayBorrowingStatistics(int borrowingCount) {
    printf("\nBorrowing Statistics:\n");
    printf("----------------------------------------\n");
    printf("Total active borrowings: %d\n", borrowingCount);
    printf("----------------------------------------\n");
}

/**
 * @brief Displays statistics about overdue borrowings
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function shows statistics about overdue borrowings.
 */
void displayOverdueStatistics(int borrowingCount) {
    time_t currentTime = time(NULL);
    int overdueCount = 0;
    int totalFine = 0;
    for (int i = 0; i < borrowingCount; i++) {
        if (currentTime > dueDate[i]) {
            overdueCount++;
            totalFine += calculateFine(dueDate[i], currentTime);
        }
    }
    printf("\n=== Overdue Statistics ===\n");
    printf("Total Borrowings: %d\n", borrowingCount);
    printf("Overdue Borrowings: %d (%.1f%%)\n", overdueCount, (float)overdueCount / borrowingCount * 100);
    printf("Total Fine: %d VND\n", totalFine);
    if (overdueCount > 0) {
        printf("Average Fine per Overdue: %.0f VND\n", (float)totalFine / overdueCount);
    }
}

/**
 * @brief Displays statistics about currently borrowed books
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function shows statistics about books that are currently borrowed.
 */
void displayCurrentlyBorrowedBooks(int borrowingCount) {
    int totalBorrowedBooks = 0;
    int activeBorrowings = 0;
    for (int i = 0; i < borrowingCount; i++) {
        if (!isReturned[i]) {
            totalBorrowedBooks += borrowingBookCount[i];
            activeBorrowings++;
        }
    }
    printf("\n=== Currently Borrowed Books Statistics ===\n");
    printf("Total Active Borrowings: %d\n", activeBorrowings);
    printf("Total Books Currently Borrowed: %d\n", totalBorrowedBooks);
    if (activeBorrowings > 0) {
        printf("Average Books per Borrowing: %.1f\n", (float)totalBorrowedBooks / activeBorrowings);
    }
}

/**
 * @brief Displays all overdue borrowings
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function shows all borrowing records that are past their due date.
 */
void displayOverdueBorrowings(int borrowingCount) {
    time_t currentTime = time(NULL);
    int found = 0;
    printf("\n=== Overdue Borrowings ===\n");
    for (int i = 0; i < borrowingCount; i++) {
        if (currentTime > dueDate[i]) {
            printf("\nBorrowing ID: %d\n", i);
            printf("Reader: %s (CMND: %s)\n", readerName[borrowingReaderID[i]], readerCMND[borrowingReaderID[i]]);
            printf("Books:\n");
            for (int j = 0; j < borrowingBookCount[i]; j++) {
                printf("- %s (ISBN: %s)\n", borrowingBooks[i][j], bookISBN[findBookByISBN(MAX_BOOKS, borrowingBooks[i][j])]);
            }
            printf("Borrow Date: %s", ctime(&borrowingDate[i]));
            printf("Due Date: %s", ctime(&dueDate[i]));
            printf("Fine: %d VND\n", calculateFine(dueDate[i], currentTime));
            found = 1;
        }
    }
    if (!found) {
        printf("No overdue borrowings found.\n");
    }
} 