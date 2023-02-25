#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include "Scenes.h"
#include "Utility.h"

int main(int argc, char **argv)
{
    InitWindow(VIEW_WIDTH, VIEW_HEIGHT, "Better Sonic The Hedgehog");
    SetWindowMinSize(VIEW_WIDTH, VIEW_HEIGHT);
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitAudioDevice();
    SetTargetFPS(FRAMERATE);

    int current_scene = 0;
    
    while (!WindowShouldClose())
    {
        switch (current_scene) {
            case 0:{profile_creator(); break;}
            default: {
                BeginDrawing();
                ClearBackground(WHITE);
                DrawTextPro(GetFontDefault(), "No scene is loaded.", (Vector2) { VIEW_WIDTH / 2 - (float)(FontGetStringWidth(GetFontDefault(), "No scene is loaded.") / 2), VIEW_HEIGHT / 2 }, (Vector2) { (float)FontGetStringWidth(GetFontDefault(), "No scene is loaded."), FontGetGlyphSize(GetFontDefault()).y / 2 }, 0, 20, 2, BLACK);
                EndDrawing();
                break;
            }
        }
    }

    CloseWindow();
    return (EXIT_SUCCESS);
}