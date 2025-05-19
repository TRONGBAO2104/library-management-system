#include "borrowing.h"
#include "reader.h"
#include "book.h"
#include "library.h"

// Define the array of borrowings
Borrowing borrowings[MAX_BORROWINGS];

// Function to calculate fines
int calculateFine(time_t dueDate, time_t returnDate) {
    if (returnDate <= dueDate) {
        return 0;
    }
    int daysLate = (returnDate - dueDate) / (24 * 60 * 60);
    return daysLate * FINE_PER_DAY;
}

/**
 * @brief Creates a new borrowing record
 * @param books Array of books in the system
 * @param bookCount Current number of books in the system
 * @param readers Array of readers in the system
 * @param readerCount Current number of readers in the system
 * @param borrowingCount Pointer to the current number of borrowings
 * @return void
 * 
 * This function creates a new borrowing record with multiple books,
 * borrowing date, and due date (7 days from borrowing date).
 */
void createBorrowing(Book books[], int bookCount, Reader readers[], int readerCount, int *borrowingCount) {
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
    if (currentTime > readers[readerIndex].cardExpiryDate) {
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

    borrowings[*borrowingCount].readerID = readerId;
    borrowings[*borrowingCount].borrowingDate = currentTime;
    borrowings[*borrowingCount].dueDate = currentTime + (7 * 24 * 60 * 60); // 7 days from now
    borrowings[*borrowingCount].bookCount = numBooks;
    borrowings[*borrowingCount].isReturned = 0;

    printf("Enter ISBN for each book:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Book %d ISBN: ", i + 1);
        scanf("%s", borrowings[*borrowingCount].books[i]);
        clearInputBuffer();

        int bookIndex = findBookByISBN(bookCount, borrowings[*borrowingCount].books[i]);
        if (bookIndex == -1) {
            printf("Book not found!\n");
            return;
        }

        if (books[bookIndex].quantity <= 0) {
            printf("Book is not available for borrowing!\n");
            return;
        }

        books[bookIndex].quantity--;
    }

    printf("Books borrowed successfully!\n");
    printf("Due date: %s\n", ctime(&borrowings[*borrowingCount].dueDate));
    (*borrowingCount)++;
}

/**
 * @brief Returns borrowed books
 * @param books Array of books in the system
 * @param bookCount Current number of books in the system
 * @param readers Array of readers in the system
 * @param readerCount Current number of readers in the system
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function handles the return of borrowed books, including
 * calculating fines for late returns.
 */
void returnBooks(Book books[], int bookCount, Reader readers[], int readerCount, int borrowingCount) {
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

    if (borrowings[borrowIndex].readerID != readerId) {
        printf("This borrowing record does not belong to the reader!\n");
        return;
    }

    if (borrowings[borrowIndex].isReturned) {
        printf("These books have already been returned!\n");
        return;
    }

    time_t currentTime = time(NULL);
    borrowings[borrowIndex].returnDate = currentTime;

    // Calculate fine if late
    int fine = calculateFine(borrowings[borrowIndex].dueDate, currentTime);
    if (fine > 0) {
        printf("Late return fine: %d VND\n", fine);
    }

    // Return all books
    for (int i = 0; i < borrowings[borrowIndex].bookCount; i++) {
        int bookIndex = findBookByISBN(bookCount, borrowings[borrowIndex].books[i]);
        if (bookIndex != -1) {
            books[bookIndex].quantity++;
        }
    }

    borrowings[borrowIndex].isReturned = 1;
    printf("Books returned successfully!\n");
    printf("Reader: %s (CMND: %s)\n", readers[readerIndex].name, readers[readerIndex].CMND);
}

/**
 * @brief Saves borrowings to file
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function saves all borrowings to a file.
 */
void saveBorrowingsToFile(int borrowingCount) {
    FILE *file = fopen("borrowings.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    // Save the number of borrowings
    fprintf(file, "%d\n", borrowingCount);
    
    // Save the information of each borrowing
    for (int i = 0; i < borrowingCount; i++) {
        fprintf(file, "%d\n", borrowings[i].readerID);
        fprintf(file, "%ld\n", borrowings[i].borrowingDate);
        fprintf(file, "%ld\n", borrowings[i].dueDate);
        fprintf(file, "%ld\n", borrowings[i].returnDate);
        fprintf(file, "%d\n", borrowings[i].bookCount);
        fprintf(file, "%d\n", borrowings[i].isReturned);
        
        // Lưu danh sách sách mượn
        for (int j = 0; j < borrowings[i].bookCount; j++) {
            fprintf(file, "%s\n", borrowings[i].books[j]);
        }
    }
    
    fclose(file);
    printf("Borrowings saved to file successfully.\n");
}

/**
 * @brief Loads borrowings from file
 * @param borrowingCount Pointer to the current number of borrowings
 * @return void
 * 
 * This function loads all borrowings from a file.
 */
void loadBorrowingsFromFile(int *borrowingCount) {
    FILE *file = fopen("borrowings.txt", "r");
    if (file == NULL) {
        printf("No existing borrowing data found.\n");
        return;
    }
    
    // Read the number of borrowings
    fscanf(file, "%d\n", borrowingCount);
    
    // Read the information of each borrowing
    for (int i = 0; i < *borrowingCount; i++) {
        fscanf(file, "%d\n", &borrowings[i].readerID);
        fscanf(file, "%ld\n", &borrowings[i].borrowingDate);
        fscanf(file, "%ld\n", &borrowings[i].dueDate);
        fscanf(file, "%ld\n", &borrowings[i].returnDate);
        fscanf(file, "%d\n", &borrowings[i].bookCount);
        fscanf(file, "%d\n", &borrowings[i].isReturned);
        
        // Read the list of borrowed books
        for (int j = 0; j < borrowings[i].bookCount; j++) {
            fgets(borrowings[i].books[j], MAX_STRING, file);
            borrowings[i].books[j][strcspn(borrowings[i].books[j], "\n")] = 0;
        }
    }
    
    fclose(file);
    printf("Borrowings loaded from file successfully.\n");
} 