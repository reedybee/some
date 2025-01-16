#include <stdlib.h>

#include "delta/delta.h"

int main(int argc, char* argv[]) {

    dtWindow* window = dtCreateWindow("Delta Test Window", DELTA_WINDOW_CENTERED, DELTA_WINDOW_CENTERED, 1920 * 0.8, 1080 * 0.8);

    while (!dtWindowShouldClose(window)) {
        dtUpdateWindow(window);
    }
    dtDestroyWindow(window);
    return 0;
}