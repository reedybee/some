GCC := gcc
CFLAGS := -Wall

CMAIN := src/main.c
COUT := out/main.exe

INCLUDES := src/

all: clean run

run: compile
	gdb -q out/main.exe

compile:
	$(GCC) $(CFLAGS) $(CMAIN) -o $(COUT) -I$(INCLUDES) -lopengl32 -lgdi32 -ldwmapi

clean:
	rm -f $(COUT) 