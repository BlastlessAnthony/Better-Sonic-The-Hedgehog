#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_config.h"
#include "scenes.h"


#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))


int main()
{
    InitWindow(VIEW_WIDTH, VIEW_HEIGHT, "Better Sonic The Hedgehog");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetWindowMinSize(VIEW_WIDTH, VIEW_HEIGHT);


    RenderTexture2D render_texture = LoadRenderTexture(VIEW_WIDTH, VIEW_HEIGHT);
    SetTextureFilter(render_texture.texture, TEXTURE_FILTER_POINT);
    
    InitAudioDevice();
    SetTargetFPS(FRAMERATE);
    int current_scene = 0;
    
    while (!WindowShouldClose())
    {
        float scale = MIN((float)GetScreenWidth() / VIEW_WIDTH, (float)GetScreenHeight() / VIEW_HEIGHT);

        BeginTextureMode(render_texture);
        ClearBackground(BLACK);
        switch (current_scene) {
        case 0: {
            profile_creator();
            break;
        }
        default: {
            DrawRectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, PINK);
            DrawTextEx(GetFontDefault(), "No scene is loaded currently.", (Vector2) {0.f, 0.f}, 15, 2, WHITE);
            break;
        }
        }


        //
        DrawFPS(2, VIEW_HEIGHT-16);
        EndTextureMode();

        BeginDrawing();
            DrawTexturePro(
                render_texture.texture, 
                (Rectangle) { 0.0f, 0.0f, (float)render_texture.texture.width, (float)-render_texture.texture.height },
                (Rectangle) {(GetScreenWidth() - ((float)VIEW_WIDTH * scale)) * 0.5f, (GetScreenHeight() - ((float)VIEW_HEIGHT * scale)) * 0.5f,
                (float)VIEW_WIDTH* scale, (float)VIEW_HEIGHT* scale}, 
                (Vector2) { 0, 0 }, 0.0f, WHITE);
        EndDrawing();
    } 
    printf("%s\n", GetResourcePath());
    UnloadRenderTexture(render_texture);
    CloseWindow();
    exit (EXIT_SUCCESS);
}