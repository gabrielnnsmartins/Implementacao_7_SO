CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
TARGET = main

SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
    $(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
    ./$(TARGET)

clean:
    rm -f $(TARGET)