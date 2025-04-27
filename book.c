#include "book.h"

/**
 * @brief Add a new book
 * @param bookCount Pointer to the current number of books
 * @return void
 * 
 * The user can enter book details and adds that book to the library (ensures all required fields are filled)
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
        if (strlen(bookISBN[*bookCount]) != 10) {
            printf("ISBN must be exactly 10 digits!\n");
        } else {
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
 * @brief Update an book
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * Update any field (press "Enter" to keep the current value of a field.
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
 * @brief Remove a book
 * @param bookCount Pointer to the current number of books
 * @return void
 * 
 * Removes a book by ISBN and shifts all subsequent books to maintain array continuity.
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
 * Displays books matched the search user input field.
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
 * @brief Displays all books
 * @param bookCount Current number of books in the library
 * @return void
 * 
 * Display detailed information about all books currently in the library.
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
 * @brief Searches for books by title
 * @param bookCount Current number of books in the system
 * @return void
 * 
 * Displays books matched the search input title.
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
 * Displays books matched the given ISBN.
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
 * @brief Searches for books by author name
 * @param bookCount Current number of books in the system
 * @return void
 * 
 *Displays books matched the search term in their author name.
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