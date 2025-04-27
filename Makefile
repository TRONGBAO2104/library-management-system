CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = library_manager
SRCS = main.c library.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.dat

.PHONY: all clean 