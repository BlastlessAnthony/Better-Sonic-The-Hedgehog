#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include "data/game_config.h"
#include "scenes/scenes.h"
#include "utilities/utility.h"
#include "assets/assets.h"



int main()
{
    InitWindow(VIEW_WIDTH, VIEW_HEIGHT, "Better Sonic The Hedgehog");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetWindowMinSize(VIEW_WIDTH, VIEW_HEIGHT);

    RenderTexture2D render_texture = LoadRenderTexture(VIEW_WIDTH, VIEW_HEIGHT);
    SetTextureFilter(render_texture.texture, TEXTURE_FILTER_POINT);
    
    InitAudioDevice();
    SetTargetFPS(FRAMERATE);

    addNewSceneToSceneTree(initialize_name_creator, update_name_creator, destroy_name_creator);
    scene_tree[0]->initialize(); 

    EmbeddedFont *f = newEmbeddedFont(".ttf", PixelOperator_Bold_ttf, PIXEL_OPERATOR_BOLD_TTF_BYTE_SIZE, 32);
    while (!WindowShouldClose())
    {
        float scale = getLetterboxRatio((Vector2) {VIEW_WIDTH, VIEW_HEIGHT});

        BeginTextureMode(render_texture);
        ClearBackground(BLACK);

        //
        if (isInDebugMode())
        {
            
        }
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(
                render_texture.texture, 
                (Rectangle) { 0.0f, 0.0f, (float)render_texture.texture.width, (float)-render_texture.texture.height },
                (Rectangle) {(GetScreenWidth() - ((float)VIEW_WIDTH * scale)) * 0.5f, (GetScreenHeight() - ((float)VIEW_HEIGHT * scale)) * 0.5f,
                (float)VIEW_WIDTH* scale, (float)VIEW_HEIGHT* scale}, 
                (Vector2) { 0, 0 }, 0.0f, WHITE);
        EndDrawing();
    }
    UnloadRenderTexture(render_texture);
    CloseWindow();
    exit (EXIT_SUCCESS);
}

