#ifndef BOOK_H
#define BOOK_H

#include "library.h"

void addBook(int *bookCount);
void updateBook(int bookCount);
void deleteBook(int *bookCount);
void searchBook(int bookCount);
void displayAllBooks(int bookCount);
void searchBookByTitle(int bookCount);
void searchBookByISBN(int bookCount);
void searchBookByAuthor(int bookCount);
void displayBookStatistics(int bookCount);

#endif // BOOK_H 