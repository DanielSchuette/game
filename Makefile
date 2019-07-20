# Make the game.
# conditional compilation options
CONFIG =
override CONFIG += -DENABLE_ESC_QUIT # quit with escape
override CONFIG += -DDEBUG # enable debug mode
override CONFIG += # -DREPORT_FPS # report framerate

# compilation flags and sources
CFLAGS      = -O3 -Wall
LDFLAGS     =
SDL_CFLAGS  = $(shell pkg-config --cflags SDL2_image)
SDL_LDFLAGS = $(shell pkg-config --libs SDL2_image)
override CFLAGS  += $(SDL_CFLAGS)
override LDFLAGS += $(SDL_LDFLAGS)

BIN         = prog
SRC_DIR     = src
SRCS        = $(wildcard $(SRC_DIR)/*.c)
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS))

.PHONY: all test clean help

all: $(BIN)

$(BIN): $(OBJS)
	gcc $(LDFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) $(CONFIG) -c $< -o $@

test: $(BIN)
	./$<

clean:
	rm -f $(SRC_DIR)/*.o $(BIN)

help:
	@echo 'make all'
