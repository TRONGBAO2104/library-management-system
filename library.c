#include "library.h"

// Global array definitions
char bookISBN[MAX_BOOKS][MAX_STRING];
char bookTitle[MAX_BOOKS][MAX_STRING];
char bookAuthor[MAX_BOOKS][MAX_STRING];
char bookPublisher[MAX_BOOKS][MAX_STRING];
int bookPublishYear[MAX_BOOKS];
char bookCategory[MAX_BOOKS][MAX_STRING];
float bookPrice[MAX_BOOKS];
int bookQuantity[MAX_BOOKS];

int readerID[MAX_READERS];
char readerName[MAX_READERS][MAX_STRING];
char readerEmail[MAX_READERS][MAX_STRING];
char readerPhone[MAX_READERS][MAX_STRING];
char readerAddress[MAX_READERS][MAX_STRING];
int readerMembershipYear[MAX_READERS];
char readerCMND[MAX_READERS][MAX_STRING];
char readerBirthDate[MAX_READERS][11];
char readerGender[MAX_READERS][10];
time_t readerCardIssueDate[MAX_READERS];
time_t readerCardExpiryDate[MAX_READERS];

int borrowingReaderID[MAX_BORROWINGS];
time_t borrowingDate[MAX_BORROWINGS];
time_t dueDate[MAX_BORROWINGS];
time_t returnDate[MAX_BORROWINGS];
int borrowingBookCount[MAX_BORROWINGS];
char borrowingBooks[MAX_BORROWINGS][MAX_BOOKS_PER_READER][MAX_STRING];
int isReturned[MAX_BORROWINGS];

/**
 * @brief Clears the input buffer to prevent input issues
 * @return void
 * 
 * This function reads and discards all characters in the input buffer
 * until it encounters a newline or EOF character.
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Validates ISBN format
 * @param isbn ISBN string to validate
 * @return int 1 if valid, 0 if invalid
 * 
 * This function checks if the ISBN is exactly 10 digits.
 */
int isValidISBN(const char *isbn) {
    if (strlen(isbn) != 10) {
        return 0;
    }
    
    for (int i = 0; i < 10; i++) {
        if (!isdigit(isbn[i])) {
            return 0;
        }
    }
    
    return 1;
}

/**
 * @brief Finds a book by its ISBN
 * @param bookCount Current number of books in the system
 * @param ISBN The ISBN to search for
 * @return int Index of the book if found, -1 otherwise
 * 
 * This function searches through the book array to find a book
 * with the matching ISBN and returns its index.
 */
int findBookByISBN(int bookCount, const char *ISBN) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(bookISBN[i], ISBN) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Finds a reader by their ID
 * @param readerCount Current number of readers in the system
 * @param id The reader ID to search for
 * @return int Index of the reader if found, -1 otherwise
 * 
 * This function searches through the reader array to find a reader
 * with the matching ID and returns their index.
 */
int findReaderByID(int readerCount, int id) {
    for (int i = 0; i < readerCount; i++) {
        if (readerID[i] == id) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Displays all borrowing records
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function shows all current borrowing records.
 */
void displayBorrowings(int borrowingCount) {
    if (borrowingCount == 0) {
        printf("No active borrowings.\n");
        return;
    }

    printf("\nActive Borrowings:\n");
    printf("----------------------------------------\n");
    // Note: In a real implementation, this would show detailed borrowing records
    printf("Total active borrowings: %d\n", borrowingCount);
    printf("----------------------------------------\n");
}

/**
 * @brief Calculates fine for late return
 * @param dueDate The due date of the borrowing
 * @param returnDate The actual return date
 * @return int The calculated fine amount
 * 
 * This function calculates the fine based on the number of days late.
 */
int calculateFine(time_t dueDate, time_t returnDate) {
    double diff = difftime(returnDate, dueDate);
    int daysLate = (int)(diff / (24 * 3600));
    if (daysLate <= 0) return 0;
    return daysLate * 5000; // 5000 VND per day
}

/**
 * @brief Calculates fine for lost book
 * @param bookPrice The price of the lost book
 * @return int The calculated fine amount
 * 
 * This function calculates the fine for a lost book.
 */
int calculateLostBookFine(float bookPrice) {
    return (int)(bookPrice * 2); // 2 times the book price
} 