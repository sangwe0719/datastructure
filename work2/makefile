CC = gcc
CFLAGS = -Wall -g
OBJS = main.o sort.o
TARGET = main.exe

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c sort.h
	$(CC) $(CFLAGS) -c main.c

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) -c sort.c

clean:
	rm -f *.o $(TARGET)
