CC = gcc
CFLAGS = -Wall -g
OBJS = main_huffman.o huffman_tree.o binary_tree.o queue.o

TARGET = huffman

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main_huffman.o: main_huffman.c huffman_tree.h binary_tree.h
	$(CC) $(CFLAGS) -c main_huffman.c

huffman_tree.o: huffman_tree.c huffman_tree.h binary_tree.h queue.h
	$(CC) $(CFLAGS) -c huffman_tree.c

binary_tree.o: binary_tree.c binary_tree.h queue.h
	$(CC) $(CFLAGS) -c binary_tree.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f *.o $(TARGET)
