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
 * @brief Calculates fine for lost book
 * @param bookPrice The price of the lost book
 * @return int The calculated fine amount
 * 
 * This function calculates the fine for a lost book.
 */
int calculateLostBookFine(float bookPrice) {
    return (int)(bookPrice * 2); // 2 times the book price
}

void displayBorrowingMenu() {
    printf("\n=== Borrowing Management ===\n");
    printf("1. Create New Borrowing\n");
    printf("2. Return Books\n");
    printf("3. Display All Borrowings\n");
    printf("4. Display Overdue Borrowings\n");
    printf("0. Back to Main Menu\n");
    printf("Enter your choice: ");
}

void borrowingManagement(int bookCount, int readerCount, int *borrowingCount) {
    int choice;
    do {
        displayBorrowingMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                createBorrowing(books, bookCount, readers, readerCount, borrowingCount);
                break;
            case 2:
                returnBooks(books, bookCount, readers, readerCount, *borrowingCount);
                break;
            case 3:
                displayBorrowings(*borrowingCount);
                break;
            case 4:
                displayOverdueBorrowings(*borrowingCount);
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
} 