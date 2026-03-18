CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = a3
SRCS = main.c sorting.c searching.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c a3.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)