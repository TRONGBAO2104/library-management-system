#ifndef BORROWING_H
#define BORROWING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "reader.h"
#include "book.h"

#define MAX_BORROWINGS 1000
#define MAX_BOOKS_PER_READER 5
#define MAX_STRING 100

// Define the Borrowing struct
typedef struct {
    int readerID;
    time_t borrowingDate;
    time_t dueDate;
    time_t returnDate;
    int bookCount;
    char books[MAX_BOOKS_PER_READER][MAX_STRING];
    int isReturned;
} Borrowing;

// Declare the borrowings array
extern Borrowing borrowings[MAX_BORROWINGS];

// Declare the functions
void createBorrowing(Book books[], int bookCount, Reader readers[], int readerCount, int *borrowingCount);
void returnBooks(Book books[], int bookCount, Reader readers[], int readerCount, int borrowingCount);
void saveBorrowingsToFile(int borrowingCount);
void loadBorrowingsFromFile(int *borrowingCount);
int calculateFine(time_t dueDate, time_t returnDate);

#endif // BORROWING_H 