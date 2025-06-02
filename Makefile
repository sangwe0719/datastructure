# 컴파일러 및 옵션
CC      = gcc
CFLAGS  = -Wall -g

# 최종 실행 파일 이름
TARGET  = mst

# 각 소스 파일로부터 생성될 오브젝트 파일 목록
OBJS    = main.o graph.o prim.o kruskal.o

# 기본 빌드: all → $(TARGET)
all: $(TARGET)

# mst 실행 파일 생성
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# main.o 컴파일 규칙
main.o: main.c graph.h prim.h kruskal.h
	$(CC) $(CFLAGS) -c main.c

# graph.o 컴파일 규칙
graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

# prim.o 컴파일 규칙
prim.o: prim.c prim.h graph.h
	$(CC) $(CFLAGS) -c prim.c

# kruskal.o 컴파일 규칙
kruskal.o: kruskal.c kruskal.h graph.h
	$(CC) $(CFLAGS) -c kruskal.c

# 뒷정리
clean:
	rm -f $(OBJS) $(TARGET)
