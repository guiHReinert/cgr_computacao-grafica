# constantes
CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lglut -lGL -lGLU -lm

SRC = buneco.c
TARGET = buneco

# compilacao basica
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

# comandos
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean

# compilacao original
# gcc buneco.c -lglut -lGL -lGLU -lm -o buneco
# ./buneco
