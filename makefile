GCC := gcc
CFLAGS := -Wall

CMAIN := src/main.c
COUT := out/main.exe

WIN32_H := src/delta/delta_win32.h
WIN32_C := src/delta/delta_win32.c
WIN32_O_OUT := out/delta_win32.o
WIN32_DLL_OUT := out/delta_win32.dll

INCLUDES := src/

LINKS := -Lout/ -lopengl32 -lgdi32 -ldwmapi -ldelta_win32

all: clean run

run: compile
	gdb -q out/main.exe

compile: dll
	$(GCC) $(CFLAGS) $(CMAIN) -o $(COUT) -I$(INCLUDES) $(LINKS)

dll: 
	gcc -c $(WIN32_C) -o $(WIN32_O_OUT) -I$(INCLUDES) $(LINKS)
	gcc -shared -o $(WIN32_DLL_OUT) $(WIN32_O_OUT) $(LINKS)
	rm -f $(WIN32_O_OUT)

clean:
	rm -f out/* 