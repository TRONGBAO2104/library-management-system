#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "constants.h"

// Define the Reader struct
typedef struct {
    int ID;
    char name[MAX_STRING];
    char CMND[MAX_STRING];
    char birthDate[MAX_STRING];
    char gender[MAX_STRING];
    char email[MAX_STRING];
    char phone[MAX_STRING];
    char address[MAX_STRING];
    time_t cardIssueDate;
    time_t cardExpiryDate;
    int membershipYear;
} Reader;

// Declare the readers array
extern Reader readers[MAX_READERS];

// Declare the functions
void addReader(int *readerCount);
void updateReader(int readerCount);
void deleteReader(int *readerCount);
void searchReader(int readerCount);
void searchReaderByCMND(int readerCount);
void displayAllReaders(int readerCount);
void displayReaderStatistics(int readerCount);
void displayGenderStatistics(int readerCount);
void searchBooksByReaderName(int borrowingCount);

// Add the functions to save data to the file
void saveReadersToFile(int readerCount);
void loadReadersFromFile(int *readerCount);
int findReaderByID(int readerCount, int id);

#endif // READER_H 