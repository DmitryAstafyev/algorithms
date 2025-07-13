CC = gcc
CFLAGS = `pkg-config --cflags sdl2`
LDFLAGS = `pkg-config --libs sdl2`
SYSFLAGS = -lm

SRC = \
	src/main.c \
	src/sorting/sorting.c \
	src/sorting/visual.c \
	src/sorting/cases/bubble.c \
	src/model/model.c \

TARGET = algorithms

all:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS) $(SYSFLAGS)

clean:
	rm -f $(TARGET)