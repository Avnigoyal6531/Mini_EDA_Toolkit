CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

TARGET = eda.exe

SRC = src/main.c src/parser.c src/graph.c src/ast.c src/sta.c src/drc.c src/optimizer.c src/power.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) src/*.o