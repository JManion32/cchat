CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -I../common
LDFLAGS = -pthread

SRC = src/main.cpp src/server.cpp ../common//src/protocol.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = ../bin/server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)