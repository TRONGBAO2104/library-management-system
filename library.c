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
 * @brief Adds a new book to the library
 * @param bookCount Pointer to the current number of books
 * @return void
 * 
 * This function prompts the user to enter book details and adds
 * the book to the library's collection. It handles input validation
 * and ensures all required fields are filled.
 */
void addBook(int *bookCount) {
    if (*bookCount >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    printf("\n=== Add New Book ===\n");
    
    // Input ISBN (10 digits)
    do {
        printf("Enter ISBN (10 digits): ");
        scanf("%s", bookISBN[*bookCount]);
        clearInputBuffer();
        
        // Check if ISBN is exactly 10 digits
        if (strlen(bookISBN[*bookCount]) != 10) {
            printf("ISBN must be exactly 10 digits!\n");
        } else {
            // Check if ISBN contains only digits
            int valid = 1;
            for (int i = 0; i < 10; i++) {
                if (!isdigit(bookISBN[*bookCount][i])) {
                    valid = 0;
                    break;
                }
            }
            if (!valid) {
                printf("ISBN must contain only digits!\n");
            } else {
                // Check if ISBN already exists
                int exists = 0;
                for (int i = 0; i < *bookCount; i++) {
                    if (strcmp(bookISBN[i], bookISBN[*bookCount]) == 0) {
                        exists = 1;
                        break;
                    }
                }
                if (exists) {
                    printf("ISBN already exists!\n");
                } else {
                    break;
                }
            }
        }
    } while (1);

    // Input other book details
    printf("Enter book title: ");
    fgets(bookTitle[*bookCount], MAX_STRING, stdin);
    bookTitle[*bookCount][strcspn(bookTitle[*bookCount], "\n")] = 0;

    printf("Enter author: ");
    fgets(bookAuthor[*bookCount], MAX_STRING, stdin);
    bookAuthor[*bookCount][strcspn(bookAuthor[*bookCount], "\n")] = 0;

    printf("Enter publisher: ");
    fgets(bookPublisher[*bookCount], MAX_STRING, stdin);
    bookPublisher[*bookCount][strcspn(bookPublisher[*bookCount], "\n")] = 0;

    printf("Enter publish year: ");
    scanf("%d", &bookPublishYear[*bookCount]);
    clearInputBuffer();

    printf("Enter category: ");
    fgets(bookCategory[*bookCount], MAX_STRING, stdin);
    bookCategory[*bookCount][strcspn(bookCategory[*bookCount], "\n")] = 0;

    printf("Enter price: ");
    scanf("%f", &bookPrice[*bookCount]);
    clearInputBuffer();

    printf("Enter quantity: ");
    scanf("%d", &bookQuantity[*bookCount]);
    clearInputBuffer();

    (*bookCount)++;
    printf("Book added successfully!\n");
}

/**
 * @brief Updates an existing book's information
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * This function allows updating any field of an existing book.
 * Users can press Enter to keep the current value of a field.
 */
void updateBook(int bookCount) {
    char ISBN[MAX_STRING];
    printf("Enter ISBN of book to update: ");
    scanf("%s", ISBN);
    clearInputBuffer();

    int index = findBookByISBN(bookCount, ISBN);
    if (index == -1) {
        printf("Book not found!\n");
        return;
    }

    printf("Enter new title (or press Enter to keep current): ");
    char title[MAX_STRING];
    fgets(title, MAX_STRING, stdin);
    title[strcspn(title, "\n")] = 0;
    if (strlen(title) > 0) strcpy(bookTitle[index], title);

    printf("Enter new author (or press Enter to keep current): ");
    char author[MAX_STRING];
    fgets(author, MAX_STRING, stdin);
    author[strcspn(author, "\n")] = 0;
    if (strlen(author) > 0) strcpy(bookAuthor[index], author);

    printf("Enter new publisher (or press Enter to keep current): ");
    char publisher[MAX_STRING];
    fgets(publisher, MAX_STRING, stdin);
    publisher[strcspn(publisher, "\n")] = 0;
    if (strlen(publisher) > 0) strcpy(bookPublisher[index], publisher);

    printf("Enter new publish year (or 0 to keep current): ");
    int year;
    scanf("%d", &year);
    clearInputBuffer();
    if (year > 0) bookPublishYear[index] = year;

    printf("Enter new category (or press Enter to keep current): ");
    char category[MAX_STRING];
    fgets(category, MAX_STRING, stdin);
    category[strcspn(category, "\n")] = 0;
    if (strlen(category) > 0) strcpy(bookCategory[index], category);

    printf("Enter new price (or 0 to keep current): ");
    float price;
    scanf("%f", &price);
    clearInputBuffer();
    if (price > 0) bookPrice[index] = price;

    printf("Enter new quantity (or -1 to keep current): ");
    int quantity;
    scanf("%d", &quantity);
    clearInputBuffer();
    if (quantity >= 0) bookQuantity[index] = quantity;

    printf("Book updated successfully!\n");
}

/**
 * @brief Removes a book from the library system
 * @param bookCount Pointer to the current number of books
 * @return void
 * 
 * This function removes a book by ISBN and shifts all subsequent
 * books to maintain array continuity.
 */
void deleteBook(int *bookCount) {
    char ISBN[MAX_STRING];
    printf("Enter ISBN of book to delete: ");
    scanf("%s", ISBN);
    clearInputBuffer();

    int index = findBookByISBN(*bookCount, ISBN);
    if (index == -1) {
        printf("Book not found!\n");
        return;
    }

    // Shift remaining books
    for (int i = index; i < *bookCount - 1; i++) {
        strcpy(bookISBN[i], bookISBN[i + 1]);
        strcpy(bookTitle[i], bookTitle[i + 1]);
        strcpy(bookAuthor[i], bookAuthor[i + 1]);
        strcpy(bookPublisher[i], bookPublisher[i + 1]);
        bookPublishYear[i] = bookPublishYear[i + 1];
        strcpy(bookCategory[i], bookCategory[i + 1]);
        bookPrice[i] = bookPrice[i + 1];
        bookQuantity[i] = bookQuantity[i + 1];
    }
    (*bookCount)--;
    printf("Book deleted successfully!\n");
}

/**
 * @brief Searches for books by title or author
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * This function displays all books that match the search term
 * in either their title or author field.
 */
void searchBook(int bookCount) {
    char searchTerm[MAX_STRING];
    printf("Enter search term (title or author): ");
    fgets(searchTerm, MAX_STRING, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(bookTitle[i], searchTerm) || strstr(bookAuthor[i], searchTerm)) {
            printf("ISBN: %s\n", bookISBN[i]);
            printf("Title: %s\n", bookTitle[i]);
            printf("Author: %s\n", bookAuthor[i]);
            printf("Publisher: %s\n", bookPublisher[i]);
            printf("Year: %d\n", bookPublishYear[i]);
            printf("Category: %s\n", bookCategory[i]);
            printf("Price: %.2f\n", bookPrice[i]);
            printf("Quantity: %d\n", bookQuantity[i]);
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found matching the search term.\n");
    }
}

/**
 * @brief Displays all books in the library system
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * This function shows detailed information about all books
 * currently in the system.
 */
void displayAllBooks(int bookCount) {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\nAll Books:\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ISBN: %s\n", bookISBN[i]);
        printf("Title: %s\n", bookTitle[i]);
        printf("Author: %s\n", bookAuthor[i]);
        printf("Publisher: %s\n", bookPublisher[i]);
        printf("Year: %d\n", bookPublishYear[i]);
        printf("Category: %s\n", bookCategory[i]);
        printf("Price: %.2f\n", bookPrice[i]);
        printf("Quantity: %d\n", bookQuantity[i]);
        printf("----------------------------------------\n");
    }
}

/**
 * @brief Adds a new reader to the library system
 * @param readerCount Pointer to the current number of readers
 * @return void
 * 
 * This function prompts the user to enter reader details,
 * validates the input, and adds the reader to the system.
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
 * @brief Updates an existing reader's information
 * @param readerCount Current number of readers in the system
 * @return void
 * 
 * This function allows updating any field of an existing reader.
 * Users can press Enter to keep the current value of a field.
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
 * @brief Removes a reader from the library system
 * @param readerCount Pointer to the current number of readers
 * @return void
 * 
 * This function removes a reader by ID and shifts all subsequent
 * readers to maintain array continuity.
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
 * This function displays all readers that match the search term
 * in either their name or email field.
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

/**
 * @brief Searches for books by title
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * This function displays all books that match the search term in their title.
 */
void searchBookByTitle(int bookCount) {
    char searchTerm[MAX_STRING];
    printf("Enter title to search: ");
    fgets(searchTerm, MAX_STRING, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(bookTitle[i], searchTerm)) {
            printf("ISBN: %s\n", bookISBN[i]);
            printf("Title: %s\n", bookTitle[i]);
            printf("Author: %s\n", bookAuthor[i]);
            printf("Publisher: %s\n", bookPublisher[i]);
            printf("Year: %d\n", bookPublishYear[i]);
            printf("Category: %s\n", bookCategory[i]);
            printf("Price: %.2f\n", bookPrice[i]);
            printf("Quantity: %d\n", bookQuantity[i]);
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found with this title.\n");
    }
}

/**
 * @brief Searches for books by ISBN
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * This function displays the book that matches the given ISBN.
 */
void searchBookByISBN(int bookCount) {
    char ISBN[MAX_STRING];
    printf("Enter ISBN to search: ");
    scanf("%s", ISBN);
    clearInputBuffer();

    int index = findBookByISBN(bookCount, ISBN);
    if (index == -1) {
        printf("Book not found!\n");
        return;
    }

    printf("\nBook Details:\n");
    printf("----------------------------------------\n");
    printf("ISBN: %s\n", bookISBN[index]);
    printf("Title: %s\n", bookTitle[index]);
    printf("Author: %s\n", bookAuthor[index]);
    printf("Publisher: %s\n", bookPublisher[index]);
    printf("Year: %d\n", bookPublishYear[index]);
    printf("Category: %s\n", bookCategory[index]);
    printf("Price: %.2f\n", bookPrice[index]);
    printf("Quantity: %d\n", bookQuantity[index]);
    printf("----------------------------------------\n");
}

/**
 * @brief Searches for readers by CMND
 * @param readerCount Current number of readers in the system
 * @return void
 * 
 * This function displays the reader that matches the given CMND.
 */
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
    
    // Calculate total value
    float totalValue = 0;
    for (int i = 0; i < bookCount; i++) {
        totalValue += bookPrice[i] * bookQuantity[i];
    }
    printf("Total value of books: %.2f\n", totalValue);

    // Count books by category
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

    // Count readers by membership year
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
 * @brief Searches for books by author name
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * This function displays all books that match the search term in their author name.
 */
void searchBookByAuthor(int bookCount) {
    char searchTerm[MAX_STRING];
    printf("Enter author name to search: ");
    fgets(searchTerm, MAX_STRING, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(bookAuthor[i], searchTerm)) {
            printf("ISBN: %s\n", bookISBN[i]);
            printf("Title: %s\n", bookTitle[i]);
            printf("Author: %s\n", bookAuthor[i]);
            printf("Publisher: %s\n", bookPublisher[i]);
            printf("Year: %d\n", bookPublishYear[i]);
            printf("Category: %s\n", bookCategory[i]);
            printf("Price: %.2f\n", bookPrice[i]);
            printf("Quantity: %d\n", bookQuantity[i]);
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found with this author name.\n");
    }
}

/**
 * @brief Searches for books borrowed by a reader's name
 * @param borrowingCount Current number of borrowings
 * @return void
 * 
 * This function displays all books that are currently borrowed by a reader
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