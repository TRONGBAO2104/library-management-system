#ifndef BORROWING_H
#define BORROWING_H

#include "library.h"

void createBorrowing(int bookCount, int readerCount, int *borrowingCount);
void returnBooks(int bookCount, int readerCount, int borrowingCount);

#endif // BORROWING_H 