#include <stdlib.h>

#include "delta/delta.h"

int main(int argc, char* argv[]) {

    deltaWindow* window = deltaCreateWindow("Meow", 1920, 1080);

    while (!deltaWindowShouldClose(window)) {
        deltaUpdateWindow(window);
    }

    return 0;
}