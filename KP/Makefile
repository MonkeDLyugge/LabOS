CC=gcc
CFLAGS=-pedantic -Wall

$(N_OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(N_OUT) $(OBJECTS)

all: A B C

A: src/A.cpp include/get_line.o
	$(CC) $(CFLAGS) src/A.cpp include/get_line.o -o A

B: src/B.cpp include/get_line.o
	$(CC) $(CFLAGS) src/B.cpp include/get_line.o -o B

C: src/C.cpp include/get_line.o
	$(CC) $(CFLAGS) src/C.cpp include/get_line.o -o C

include/get_line.o: include/get_line.cpp include/get_line.h
	$(CC) $(CFLAGS) include/get_line.cpp -c -o include/get_line.o

run: build/A build/B build/C
	./build/A

.PHONY: clean
clean:
	rm -f A B C include/get_line.o