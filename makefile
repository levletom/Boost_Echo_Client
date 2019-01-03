# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall  -std=c++11
# LFLAGS  = -L/usr/lib
LDFLAGS = -lboost_system -lpthread

# All Targets
all: BGSclient

# Tool invocations
# Executable "hello" depends on the files hello.o and run.o.
BGSclient: bin/connectionHandler.o bin/TaskReadFromSTDINWriteToSocket.o bin/TaskWriteToStdOUTReadFromSocket.o bin/echoClient.o $(LDFLAGS)
	@echo 'Building target: hello'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/BGSclient  bin/connectionHandler.o bin/TaskReadFromSTDINWriteToSocket.o bin/TaskWriteToStdOUTReadFromSocket.o bin/echoClient.o $(LDFLAGS)
	@echo 'Finished building target: BGSclient'
	@echo ' '

bin/echoClient.o: src/echoClient.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/echoClient.o src/echoClient.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/connectionHandler.o src/connectionHandler.cpp

bin/TaskWriteToStdOUTReadFromSocket.o: src/TaskWriteToStdOUTReadFromSocket.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/TaskWriteToStdOUTReadFromSocket.o src/TaskWriteToStdOUTReadFromSocket.cpp


bin/TaskReadFromSTDINWriteToSocket.o: src/TaskReadFromSTDINWriteToSocket.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/TaskReadFromSTDINWriteToSocket.o src/TaskReadFromSTDINWriteToSocket.cpp
#Clean the build directory
clean: 
	rm -f bin/*
