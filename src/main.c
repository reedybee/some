#include <stdlib.h>

#include "delta/delta.h"

int main(int argc, char* argv[]) {

    deltaWindow* window = deltaCreateWindow("Meow", 0, 0, 1920 * 0.8, 1080 * 0.8);

    while (!deltaWindowShouldClose(window)) {
        deltaUpdateWindow(window);
    }
    deltaDestroyWindow(window);
    return 0;
}