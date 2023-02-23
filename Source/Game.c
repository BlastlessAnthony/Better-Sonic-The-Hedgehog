#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include "Scenes.h"

int main(int argc, char **argv)
{
    InitWindow(VIEW_WIDTH, VIEW_HEIGHT, "Better Sonic The Hedgehog");
    InitAudioDevice();
    SetTargetFPS(FRAMERATE);

    int current_scene = 0;



    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        switch (current_scene) {
            case 0:{profile_creator(); break;}
            default: {
                DrawText("No scene here.", VIEW_WIDTH/2, VIEW_HEIGHT/2, 30, BLACK);
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return (EXIT_SUCCESS);
}