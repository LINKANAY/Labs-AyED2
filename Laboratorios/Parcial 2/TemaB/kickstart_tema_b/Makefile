TARGET  = main
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)
LIBS =

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
VALGRICOMAND = valgrind --leak-check=full 
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)

valgri:
	$(VALGRICOMAND) ./$(TARGET)

run:
	./$(TARGET)