CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -I../shared

OBJ = \
    src/main.o \
    src/client_thread.o \
    src/server.o \
    src/client.o \
    ../shared/src/socket_handler.o \
    ../shared/src/thread_handler.o

../bin/server: $(OBJ)
	$(CXX) $(OBJ) -o ../bin/server -pthread

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

../shared/src/%.o: ../shared/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o ../shared/src/*.o ../bin/server
