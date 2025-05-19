#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "constants.h"
#include "book.h"
#include "reader.h"
#include "borrowing.h"

// Maximum lengths for strings
#define MAX_STRING 100
#define MAX_BOOKS 1000
#define MAX_READERS 1000
#define MAX_BORROWINGS 1000
#define MAX_BOOKS_PER_READER 5
#define MAX_DAYS 14
#define FINE_PER_DAY 5000

// Book data arrays
extern char bookISBN[MAX_BOOKS][MAX_STRING];    // ISBN of each book
extern char bookTitle[MAX_BOOKS][MAX_STRING];   // Title of each book
extern char bookAuthor[MAX_BOOKS][MAX_STRING];  // Author of each book
extern char bookPublisher[MAX_BOOKS][MAX_STRING]; // Publisher of each book
extern int bookPublishYear[MAX_BOOKS];               // Publish year of each book
extern char bookCategory[MAX_BOOKS][MAX_STRING]; // Category of each book
extern float bookPrice[MAX_BOOKS];                   // Price of each book
extern int bookQuantity[MAX_BOOKS];                  // Quantity of each book

// Reader data arrays
extern int readerID[MAX_READERS];                    // ID of each reader
extern char readerName[MAX_READERS][MAX_STRING]; // Name of each reader
extern char readerEmail[MAX_READERS][MAX_STRING]; // Email of each reader
extern char readerPhone[MAX_READERS][MAX_STRING]; // Phone of each reader
extern char readerAddress[MAX_READERS][MAX_STRING]; // Address of each reader
extern int readerMembershipYear[MAX_READERS];        // Membership year of each reader
extern char readerCMND[MAX_READERS][MAX_STRING];
extern char readerBirthDate[MAX_READERS][11]; // Format: YYYY-MM-DD
extern char readerGender[MAX_READERS][10]; // "Male" or "Female"
extern time_t readerCardIssueDate[MAX_READERS];
extern time_t readerCardExpiryDate[MAX_READERS];

// Borrowing data arrays
extern int borrowingReaderID[MAX_BORROWINGS];
extern time_t borrowingDate[MAX_BORROWINGS];
extern time_t dueDate[MAX_BORROWINGS];
extern time_t returnDate[MAX_BORROWINGS];
extern int borrowingBookCount[MAX_BORROWINGS];
extern char borrowingBooks[MAX_BORROWINGS][MAX_BOOKS_PER_READER][MAX_STRING];
extern int isReturned[MAX_BORROWINGS];

// Function declarations with detailed comments

/**
 * @brief Adds a new book to the library system
 * @param bookCount Pointer to the current number of books
 * @return void
 * 
 * This function prompts the user to enter book details and adds them to the system.
 * It validates the ISBN format and checks for duplicates before adding.
 */
void addBook(int *bookCount);

/**
 * @brief Updates information of an existing book
 * @param bookCount Current number of books
 * @return void
 * 
 * This function allows updating any field of an existing book by ISBN.
 * Empty inputs will keep the current values unchanged.
 */
void updateBook(int bookCount);

/**
 * @brief Removes a book from the library system
 * @param bookCount Pointer to the current number of books
 * @return void
 * 
 * This function removes a book by ISBN and shifts remaining books to maintain array order.
 */
void deleteBook(int *bookCount);

/**
 * @brief Searches for books by title or author
 * @param bookCount Current number of books
 * @return void
 * 
 * This function displays all books that match the search term in either title or author.
 */
void searchBook(int bookCount);

/**
 * @brief Displays all books in the library
 * @param bookCount Current number of books
 * @return void
 * 
 * This function shows a formatted list of all books in the system.
 */
void displayAllBooks(int bookCount);

/**
 * @brief Adds a new reader to the library system
 * @param readerCount Pointer to the current number of readers
 * @return void
 * 
 * This function prompts the user to enter reader details and adds them to the system.
 * It validates the reader ID and checks for duplicates before adding.
 */
void addReader(int *readerCount);

/**
 * @brief Updates information of an existing reader
 * @param readerCount Current number of readers
 * @return void
 * 
 * This function allows updating any field of an existing reader by ID.
 * Empty inputs will keep the current values unchanged.
 */
void updateReader(int readerCount);

/**
 * @brief Removes a reader from the library system
 * @param readerCount Pointer to the current number of readers
 * @return void
 * 
 * This function removes a reader by ID and shifts remaining readers to maintain array order.
 */
void deleteReader(int *readerCount);

/**
 * @brief Searches for readers by name or email
 * @param readerCount Current number of readers
 * @return void
 * 
 * This function displays all readers that match the search term in either name or email.
 */
void searchReader(int readerCount);

/**
 * @brief Displays all readers in the library
 * @param readerCount Current number of readers
 * @return void
 * 
 * This function shows a formatted list of all readers in the system.
 */
void displayAllReaders(int readerCount);

/**
 * @brief Validates ISBN format
 * @param ISBN The ISBN to validate
 * @return int 1 if valid, 0 if invalid
 * 
 * This function checks if the ISBN is exactly 13 digits.
 */
int isValidISBN(const char *ISBN);

/**
 * @brief Finds a book by ISBN
 * @param bookCount Current number of books
 * @param ISBN The ISBN to search for
 * @return int Index of the book if found, -1 if not found
 */
int findBookByISBN(int bookCount, const char *ISBN);

/**
 * @brief Finds a reader by ID
 * @param readerCount Current number of readers
 * @param readerID The ID to search for
 * @return int Index of the reader if found, -1 if not found
 */
int findReaderByID(int readerCount, int readerID);

/**
 * @brief Clears the input buffer
 * @return void
 * 
 * This function removes any remaining characters from the input buffer.
 */
void clearInputBuffer();

// New function declarations
void searchBookByTitle(int bookCount);
void searchBookByISBN(int bookCount);
void searchBookByAuthor(int bookCount);
void searchReaderByCMND(int readerCount);
void displayBorrowings(int borrowingCount);
void displayOverdueBorrowings(int borrowingCount);
void displayBookStatistics(int bookCount);
void displayReaderStatistics(int readerCount);
void displayGenderStatistics(int readerCount);
void displayOverdueStatistics(int borrowingCount);
int calculateFine(time_t dueDate, time_t returnDate);
int calculateLostBookFine(float bookPrice);
void displayCurrentlyBorrowedBooks(int borrowingCount);
void searchBooksByReaderName(int borrowingCount);

// Function declarations
void displayMainMenu();
void displayBookMenu();
void displayReaderMenu();
void displayBorrowingMenu();
void displayStatsMenu();

// Book management functions
void bookManagement(int *bookCount);
void updateBook(int bookCount);
void deleteBook(int *bookCount);
void searchBook(int bookCount);
void searchBookByTitle(int bookCount);
void searchBookByISBN(int bookCount);
void displayAllBooks(int bookCount);

// Reader management functions
void readerManagement(int *readerCount);
void addReader(int *readerCount);
void updateReader(int readerCount);
void deleteReader(int *readerCount);
void searchReader(int readerCount);
void searchReaderByCMND(int readerCount);
void displayAllReaders(int readerCount);

// Borrowing management functions
void borrowingManagement(int bookCount, int readerCount, int *borrowingCount);
void displayBorrowings(int borrowingCount);
void displayOverdueBorrowings(int borrowingCount);

// Statistics functions
void statistics(int bookCount, int readerCount, int borrowingCount);
void displayBookStatistics(int bookCount);
void displayReaderStatistics(int readerCount);
void displayGenderStatistics(int readerCount);
void displayBorrowingStatistics(int borrowingCount);
void displayOverdueStatistics(int borrowingCount);

// File operations
void saveAllData(int bookCount, int readerCount, int borrowingCount);
void loadAllData(int *bookCount, int *readerCount, int *borrowingCount);

#endif // LIBRARY_H 