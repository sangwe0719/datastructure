CC = gcc
CFLAGS = -Wall -g

# 객체 파일들
OBJS = main.o match.o postfix.o stack.o

# 최종 실행 파일
TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c match.h stack.h postfix.h
	$(CC) $(CFLAGS) -c main.c

match.o: match.c match.h stack.h
	$(CC) $(CFLAGS) -c match.c

postfix.o: postfix.c postfix.h stack.h
	$(CC) $(CFLAGS) -c postfix.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f $(OBJS) $(TARGET)
