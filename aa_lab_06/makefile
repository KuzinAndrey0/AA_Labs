PREFIX_SRC = ./src
PREFIX_OBJ = ./out
PREFIX_HEAD = ./inc

CC = g++
CFLAGS = -std=c++20 -O0 -g3

release : app.exe

OBJ_NAMES = measurement.o algo.o general.o csr_matrix.o
OBJS = $(patsubst %,$(PREFIX_OBJ)/%,$(OBJ_NAMES))

HEAD_NAMES = measurement.h general.h algo.h csr_matrix.h
HEADERS = $(patsubst %,$(PREFIX_HEAD)/%,$(OBJ_HEAD))


app.exe: $(OBJS) ./out/main.o $(HEADERS)
	mkdir -p $(PREFIX_OBJ)
	$(CC) -o app.exe $(OBJS) ./out/main.o


$(PREFIX_OBJ)/%.o: $(PREFIX_SRC)/%.cpp $(HEADERS)
	mkdir -p $(PREFIX_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

./out/main.o: ./src/main.cpp
	$(CC) $(CFLAGS) -c $(PREFIX_SRC)/main.cpp -o $(PREFIX_OBJ)/main.o

.PHONY: clean

clean:
	rm -f *.exe
	rm -rf ./out

