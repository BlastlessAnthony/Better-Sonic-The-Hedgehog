#include <raylib.h>
#include <stdlib.h>
#include "Config.h"

int main(int argc, char **argv)
{
    InitWindow(VIEW_WIDTH, VIEW_HEIGHT, "Better Sonic The Hedgehog");
    SetTargetFPS(FRAMERATE);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return (EXIT_SUCCESS);
}