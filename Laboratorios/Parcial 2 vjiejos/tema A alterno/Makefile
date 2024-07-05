CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = pqueue.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = dispatch_patients

.PHONY: clean

all: $(TARGET)


valgrind: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET)  input/hospital_a.in

	valgrind --leak-check=full --show-reachable=yes ./$(TARGET)  input/hospital_b.in
	
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET)  input/hospital_c.in

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

