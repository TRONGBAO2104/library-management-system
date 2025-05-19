#include "book.h"
#include "library.h"
#include <ctype.h>

// Define the array of books
Book books[MAX_BOOKS];

// Function to find a book by ISBN
int findBookByISBN(int bookCount, const char *ISBN) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, ISBN) == 0) {
            return i;
        }
    }
    return -1;
}

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
        scanf("%s", books[*bookCount].ISBN);
        clearInputBuffer();
        if (strlen(books[*bookCount].ISBN) != 10) {
            printf("ISBN must be exactly 10 digits!\n");
        } else {
            int valid = 1;
            for (int i = 0; i < 10; i++) {
                if (!isdigit(books[*bookCount].ISBN[i])) {
                    valid = 0;
                    break;
                }
            }
            if (!valid) {
                printf("ISBN must contain only digits!\n");
            } else {
                int exists = 0;
                for (int i = 0; i < *bookCount; i++) {
                    if (strcmp(books[i].ISBN, books[*bookCount].ISBN) == 0) {
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
    fgets(books[*bookCount].title, MAX_STRING, stdin);
    books[*bookCount].title[strcspn(books[*bookCount].title, "\n")] = 0;

    printf("Enter author: ");
    fgets(books[*bookCount].author, MAX_STRING, stdin);
    books[*bookCount].author[strcspn(books[*bookCount].author, "\n")] = 0;

    printf("Enter publisher: ");
    fgets(books[*bookCount].publisher, MAX_STRING, stdin);
    books[*bookCount].publisher[strcspn(books[*bookCount].publisher, "\n")] = 0;

    printf("Enter publish year: ");
    scanf("%d", &books[*bookCount].publishYear);
    clearInputBuffer();

    printf("Enter category: ");
    fgets(books[*bookCount].category, MAX_STRING, stdin);
    books[*bookCount].category[strcspn(books[*bookCount].category, "\n")] = 0;

    printf("Enter price: ");
    scanf("%f", &books[*bookCount].price);
    clearInputBuffer();

    printf("Enter quantity: ");
    scanf("%d", &books[*bookCount].quantity);
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
    if (strlen(title) > 0) strcpy(books[index].title, title);

    printf("Enter new author (or press Enter to keep current): ");
    char author[MAX_STRING];
    fgets(author, MAX_STRING, stdin);
    author[strcspn(author, "\n")] = 0;
    if (strlen(author) > 0) strcpy(books[index].author, author);

    printf("Enter new publisher (or press Enter to keep current): ");
    char publisher[MAX_STRING];
    fgets(publisher, MAX_STRING, stdin);
    publisher[strcspn(publisher, "\n")] = 0;
    if (strlen(publisher) > 0) strcpy(books[index].publisher, publisher);

    printf("Enter new publish year (or 0 to keep current): ");
    int year;
    scanf("%d", &year);
    clearInputBuffer();
    if (year > 0) books[index].publishYear = year;

    printf("Enter new category (or press Enter to keep current): ");
    char category[MAX_STRING];
    fgets(category, MAX_STRING, stdin);
    category[strcspn(category, "\n")] = 0;
    if (strlen(category) > 0) strcpy(books[index].category, category);

    printf("Enter new price (or 0 to keep current): ");
    float price;
    scanf("%f", &price);
    clearInputBuffer();
    if (price > 0) books[index].price = price;

    printf("Enter new quantity (or -1 to keep current): ");
    int quantity;
    scanf("%d", &quantity);
    clearInputBuffer();
    if (quantity >= 0) books[index].quantity = quantity;

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
        books[i] = books[i + 1];
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
        if (strstr(books[i].title, searchTerm) || strstr(books[i].author, searchTerm)) {
            printf("ISBN: %s\n", books[i].ISBN);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Publisher: %s\n", books[i].publisher);
            printf("Publish Year: %d\n", books[i].publishYear);
            printf("Category: %s\n", books[i].category);
            printf("Price: %.2f\n", books[i].price);
            printf("Quantity: %d\n", books[i].quantity);
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
        printf("ISBN: %s\n", books[i].ISBN);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Publisher: %s\n", books[i].publisher);
        printf("Publish Year: %d\n", books[i].publishYear);
        printf("Category: %s\n", books[i].category);
        printf("Price: %.2f\n", books[i].price);
        printf("Quantity: %d\n", books[i].quantity);
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
    printf("Enter book title to search: ");
    fgets(searchTerm, MAX_STRING, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, searchTerm)) {
            printf("ISBN: %s\n", books[i].ISBN);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Publisher: %s\n", books[i].publisher);
            printf("Publish Year: %d\n", books[i].publishYear);
            printf("Category: %s\n", books[i].category);
            printf("Price: %.2f\n", books[i].price);
            printf("Quantity: %d\n", books[i].quantity);
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found matching the title.\n");
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
    char searchTerm[MAX_STRING];
    printf("Enter ISBN to search: ");
    scanf("%s", searchTerm);
    clearInputBuffer();

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, searchTerm) == 0) {
            printf("ISBN: %s\n", books[i].ISBN);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Publisher: %s\n", books[i].publisher);
            printf("Publish Year: %d\n", books[i].publishYear);
            printf("Category: %s\n", books[i].category);
            printf("Price: %.2f\n", books[i].price);
            printf("Quantity: %d\n", books[i].quantity);
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found matching the ISBN.\n");
    }
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
    printf("Enter author to search: ");
    fgets(searchTerm, MAX_STRING, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    printf("\nSearch Results:\n");
    printf("----------------------------------------\n");
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].author, searchTerm)) {
            printf("ISBN: %s\n", books[i].ISBN);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Publisher: %s\n", books[i].publisher);
            printf("Publish Year: %d\n", books[i].publishYear);
            printf("Category: %s\n", books[i].category);
            printf("Price: %.2f\n", books[i].price);
            printf("Quantity: %d\n", books[i].quantity);
            printf("----------------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found matching the author.\n");
    }
}

// Update the function to save data to the file
void saveBooksToFile(int bookCount) {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    // Save the number of books
    fprintf(file, "%d\n", bookCount);
    
    // Save the information of each book
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s\n", books[i].ISBN);
        fprintf(file, "%s\n", books[i].title);
        fprintf(file, "%s\n", books[i].author);
        fprintf(file, "%s\n", books[i].publisher);
        fprintf(file, "%d\n", books[i].publishYear);
        fprintf(file, "%s\n", books[i].category);
        fprintf(file, "%.2f\n", books[i].price);
        fprintf(file, "%d\n", books[i].quantity);
    }
    
    fclose(file);
    printf("Books saved to file successfully.\n");
}

// Update the function to read data from the file
void loadBooksFromFile(int *bookCount) {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("No existing book data found.\n");
        return;
    }
    
    // Read the number of books
    fscanf(file, "%d\n", bookCount);
    
    // Read the information of each book
    for (int i = 0; i < *bookCount; i++) {
        fgets(books[i].ISBN, MAX_STRING, file);
        books[i].ISBN[strcspn(books[i].ISBN, "\n")] = 0;
        
        fgets(books[i].title, MAX_STRING, file);
        books[i].title[strcspn(books[i].title, "\n")] = 0;
        
        fgets(books[i].author, MAX_STRING, file);
        books[i].author[strcspn(books[i].author, "\n")] = 0;
        
        fgets(books[i].publisher, MAX_STRING, file);
        books[i].publisher[strcspn(books[i].publisher, "\n")] = 0;
        
        fscanf(file, "%d\n", &books[i].publishYear);
        
        fgets(books[i].category, MAX_STRING, file);
        books[i].category[strcspn(books[i].category, "\n")] = 0;
        
        fscanf(file, "%f\n", &books[i].price);
        fscanf(file, "%d\n", &books[i].quantity);
    }
    
    fclose(file);
    printf("Books loaded from file successfully.\n");
} 