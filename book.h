#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

// Define the Book struct
typedef struct {
    char ISBN[MAX_STRING];
    char title[MAX_STRING];
    char author[MAX_STRING];
    char publisher[MAX_STRING];
    int publishYear;
    char category[MAX_STRING];
    float price;
    int quantity;
} Book;

// Declare the books array
extern Book books[MAX_BOOKS];

// Declare the functions
void addBook(int *bookCount);
void updateBook(int bookCount);
void deleteBook(int *bookCount);
void searchBook(int bookCount);
void searchBookByTitle(int bookCount);
void searchBookByISBN(int bookCount);
void displayAllBooks(int bookCount);
void saveBooksToFile(int bookCount);
void loadBooksFromFile(int *bookCount);
int findBookByISBN(int bookCount, const char *ISBN);

#endif // BOOK_H 