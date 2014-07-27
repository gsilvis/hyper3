CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=gnu99 -lm
#CFLAGS += -O3
#CFLAGS += -march=native
#CFLAGS += -fdata-sections -ffunction-sections
#CFLAGS += -g
CFLAGS += `pkg-config --cflags glew`
CFLAGS += `sdl-config --cflags`
LDFLAGS = $(CFLAGS) `pkg-config --libs glew`
LDFLAGS += `sdl-config --libs`
#LDFLAGS += -Wl,--gc-sections

CFILES = src/main.c src/matrix.c src/view.c src/shaders.c src/model.c
OFILES = $(patsubst %.c, %.o, $(CFILES))

all: test

test: $(OFILES)
	gcc -o $@ $^ $(LDFLAGS)

%.o : %.c
	gcc -c -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OFILES) test

