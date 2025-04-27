#include "borrowing.h"

/**
 * @brief Creates a new borrowing record
 * @param bookCount Current number of books in the system
 * @param readerCount Current number of readers in the system
 * @param borrowingCount Pointer to the current number of borrowings
 * @return void
 * 
 * This function creates a new borrowing record with multiple books,
 * borrowing date, and due date (7 days from borrowing date).
 */
void createBorrowing(int bookCount, int readerCount, int *borrowingCount) {
    if (*borrowingCount >= MAX_BORROWINGS) {
        printf("Maximum number of borrowings reached!\n");
        return;
    }

    int readerId;
    printf("Enter reader ID: ");
    scanf("%d", &readerId);
    clearInputBuffer();

    int readerIndex = findReaderByID(readerCount, readerId);
    if (readerIndex == -1) {
        printf("Reader not found!\n");
        return;
    }

    // Check if reader's card is expired
    time_t currentTime = time(NULL);
    if (currentTime > readerCardExpiryDate[readerIndex]) {
        printf("Reader's card has expired!\n");
        return;
    }

    printf("Enter number of books to borrow (max %d): ", MAX_BOOKS_PER_READER);
    int numBooks;
    scanf("%d", &numBooks);
    clearInputBuffer();

    if (numBooks <= 0 || numBooks > MAX_BOOKS_PER_READER) {
        printf("Invalid number of books!\n");
        return;
    }

    borrowingReaderID[*borrowingCount] = readerId;
    borrowingDate[*borrowingCount] = currentTime;
    dueDate[*borrowingCount] = currentTime + (7 * 24 * 60 * 60); // 7 days from now
    borrowingBookCount[*borrowingCount] = numBooks;
    isReturned[*borrowingCount] = 0;

    printf("Enter ISBN for each book:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Book %d ISBN: ", i + 1);
        scanf("%s", borrowingBooks[*borrowingCount][i]);
        clearInputBuffer();

        int bookIndex = findBookByISBN(bookCount, borrowingBooks[*borrowingCount][i]);
        if (bookIndex == -1) {
            printf("Book not found!\n");
            return;
        }

        if (bookQuantity[bookIndex] <= 0) {
            printf("Book is not available for borrowing!\n");
            return;
        }

        bookQuantity[bookIndex]--;
    }

    printf("Books borrowed successfully!\n");
    printf("Due date: %s\n", ctime(&dueDate[*borrowingCount]));
    (*borrowingCount)++;
}

/**
 * @brief Returns borrowed books
 * @param bookCount Current number of books in the system
 * @param readerCount Current number of readers in the system
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function handles the return of borrowed books, including
 * calculating fines for late returns.
 */
void returnBooks(int bookCount, int readerCount, int borrowingCount) {
    int readerId;
    printf("Enter reader ID: ");
    scanf("%d", &readerId);
    clearInputBuffer();

    int readerIndex = findReaderByID(readerCount, readerId);
    if (readerIndex == -1) {
        printf("Reader not found!\n");
        return;
    }

    printf("Enter borrowing index to return: ");
    int borrowIndex;
    scanf("%d", &borrowIndex);
    clearInputBuffer();

    if (borrowIndex < 0 || borrowIndex >= borrowingCount) {
        printf("Invalid borrowing index!\n");
        return;
    }

    if (borrowingReaderID[borrowIndex] != readerId) {
        printf("This borrowing record does not belong to the reader!\n");
        return;
    }

    if (isReturned[borrowIndex]) {
        printf("These books have already been returned!\n");
        return;
    }

    time_t currentTime = time(NULL);
    returnDate[borrowIndex] = currentTime;

    // Calculate fine if late
    int fine = calculateFine(dueDate[borrowIndex], currentTime);
    if (fine > 0) {
        printf("Late return fine: %d VND\n", fine);
    }

    // Return all books
    for (int i = 0; i < borrowingBookCount[borrowIndex]; i++) {
        int bookIndex = findBookByISBN(bookCount, borrowingBooks[borrowIndex][i]);
        if (bookIndex != -1) {
            bookQuantity[bookIndex]++;
        }
    }

    isReturned[borrowIndex] = 1;
    printf("Books returned successfully!\n");
} 