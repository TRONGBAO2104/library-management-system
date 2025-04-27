#include "library.h"
#include "reader.h"
#include "book.h"

/**
 * @brief Displays the main menu of the program
 * @return void
 * 
 * This function shows the main menu options to the user,
 * including book management, reader management, borrowing management,
 * statistics, and exit options.
 */
void displayMenu() {
    printf("\n=== Library Management System ===\n");
    printf("1. Book Management\n");
    printf("2. Reader Management\n");
    printf("3. Borrowing Management\n");
    printf("4. Statistics\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

/**
 * @brief Displays and handles the book management menu
 * @param bookCount Pointer to the current number of books
 * @return void
 * 
 * This function shows the book management options and handles user input.
 * It provides options for adding, updating, deleting, searching, and
 * displaying books.
 */
void bookManagementMenu(int *bookCount) {
    int choice;
    do {
        printf("\n=== Book Management ===\n");
        printf("1. Add Book\n");
        printf("2. Update Book\n");
        printf("3. Delete Book\n");
        printf("4. Search Book by Title\n");
        printf("5. Search Book by ISBN\n");
        printf("6. Search Book by Author\n");
        printf("7. Display All Books\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addBook(bookCount);
                break;
            case 2:
                updateBook(*bookCount);
                break;
            case 3:
                deleteBook(bookCount);
                break;
            case 4:
                searchBookByTitle(*bookCount);
                break;
            case 5:
                searchBookByISBN(*bookCount);
                break;
            case 6:
                searchBookByAuthor(*bookCount);
                break;
            case 7:
                displayAllBooks(*bookCount);
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

/**
 * @brief Displays and handles the reader management menu
 * @param readerCount Pointer to the current number of readers
 * @return void
 * 
 * This function shows the reader management options and handles user input.
 * It provides options for adding, updating, deleting, searching, and
 * displaying readers.
 */
void readerManagementMenu(int *readerCount) {
    int choice;
    do {
        printf("\n=== Reader Management ===\n");
        printf("1. Add Reader\n");
        printf("2. Update Reader\n");
        printf("3. Delete Reader\n");
        printf("4. Search Reader by Name/Email\n");
        printf("5. Search Reader by CMND\n");
        printf("6. Search Books by Reader Name\n");
        printf("7. Display All Readers\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addReader(readerCount);
                break;
            case 2:
                updateReader(*readerCount);
                break;
            case 3:
                deleteReader(readerCount);
                break;
            case 4:
                searchReader(*readerCount);
                break;
            case 5:
                searchReaderByCMND(*readerCount);
                break;
            case 6:
                searchBooksByReaderName(*readerCount);
                break;
            case 7:
                displayAllReaders(*readerCount);
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

/**
 * @brief Displays and handles the borrowing management menu
 * @param bookCount Current number of books in the system
 * @param readerCount Current number of readers in the system
 * @param borrowingCount Pointer to the current number of borrowings
 * @return void
 * 
 * This function shows the borrowing management options and handles user input.
 * It provides options for creating new borrowings, returning books, and
 * displaying borrowing records.
 */
void borrowingManagementMenu(int bookCount, int readerCount, int *borrowingCount) {
    int choice;
    do {
        printf("\n=== Borrowing Management ===\n");
        printf("1. Create New Borrowing\n");
        printf("2. Return Books\n");
        printf("3. Display All Borrowings\n");
        printf("4. Display Overdue Borrowings\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                createBorrowing(bookCount, readerCount, borrowingCount);
                break;
            case 2:
                returnBooks(bookCount, readerCount, *borrowingCount);
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
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

/**
 * @brief Displays and handles the statistics menu
 * @param bookCount Current number of books in the system
 * @param readerCount Current number of readers in the system
 * @param borrowingCount Current number of borrowings in the system
 * @return void
 * 
 * This function shows the statistics options and handles user input.
 * It provides options for viewing various statistics about books,
 * readers, and borrowings.
 */
void statisticsMenu(int bookCount, int readerCount, int borrowingCount) {
    int choice;
    do {
        printf("\n=== Statistics ===\n");
        printf("1. Book Statistics\n");
        printf("2. Reader Statistics\n");
        printf("3. Gender Statistics\n");
        printf("4. Overdue Statistics\n");
        printf("5. Currently Borrowed Books Statistics\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                displayBookStatistics(bookCount);
                break;
            case 2:
                displayReaderStatistics(readerCount);
                break;
            case 3:
                displayGenderStatistics(readerCount);
                break;
            case 4:
                displayOverdueStatistics(borrowingCount);
                break;
            case 5:
                displayCurrentlyBorrowedBooks(borrowingCount);
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

/**
 * @brief Main function of the program
 * @return int 0 on successful execution
 * 
 * This function initializes the program and handles the main menu loop.
 * It manages the overall program flow and user interaction.
 */
int main() {
    int bookCount = 0;
    int readerCount = 0;
    int borrowingCount = 0;
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                bookManagementMenu(&bookCount);
                break;
            case 2:
                readerManagementMenu(&readerCount);
                break;
            case 3:
                borrowingManagementMenu(bookCount, readerCount, &borrowingCount);
                break;
            case 4:
                statisticsMenu(bookCount, readerCount, borrowingCount);
                break;
            case 0:
                printf("Thank you for using the Library Management System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
} 