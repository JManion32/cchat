CXX = g++
QT_DIR = $(HOME)/Qt/6.10.1/gcc_64

INCLUDEPATHS = -Iinclude -I../common \
               -I$(QT_DIR)/include \
               -I$(QT_DIR)/include/QtCore \
               -I$(QT_DIR)/include/QtGui \
               -I$(QT_DIR)/include/QtWidgets \
               -I$(QT_DIR)/include/QtNetwork

LIBPATHS = -L$(QT_DIR)/lib

LIBS = -lQt6Core -lQt6Gui -lQt6Widgets -lQt6Network

CXXFLAGS = -std=c++17 -Wall $(INCLUDEPATHS)
LDFLAGS = $(LIBPATHS) $(LIBS)

SRC = src/main.cpp src/client.cpp ../common/src/protocol.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = ../bin/client

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
