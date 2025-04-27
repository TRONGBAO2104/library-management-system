#ifndef READER_H
#define READER_H

#include "library.h"

void addReader(int *readerCount);
void updateReader(int readerCount);
void deleteReader(int *readerCount);
void searchReader(int readerCount);
void displayAllReaders(int readerCount);
void searchReaderByCMND(int readerCount);
void displayReaderStatistics(int readerCount);
void displayGenderStatistics(int readerCount);
void searchBooksByReaderName(int borrowingCount);

#endif // READER_H 