CXX = g++
CXXFLAGS = -g -Wall

TARGET = main.exe

SRCS = main.cpp matrix.cpp csparsematrix.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm *.o *.exe