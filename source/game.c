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
    SetExitKey(NULL);

    RenderTexture2D render_texture = LoadRenderTexture(VIEW_WIDTH, VIEW_HEIGHT);
    SetTextureFilter(render_texture.texture, TEXTURE_FILTER_POINT);
    
    InitAudioDevice();
    SetTargetFPS(FRAMERATE);

    Image window_icon = LoadImageFromMemory(".png", bettersonic_icon_png, BETTER_SONIC_ICON_BYTE_SIZE);
    SetWindowIcon(window_icon);

    float window_opacity = 1.0f;
    unsigned int game_end = 0;
    /***************************************/


    scene_tree_t *scene_tree = newSceneTree();
    /***************************************/

    scene_t *k = newScene(initialize_name_creator, update_name_creator, destroy_name_creator);
    scene_tree = addSceneToSceneTree(scene_tree, k);
    while (!game_end)
    {
        game_end = (unsigned int)WindowShouldClose();
        float scale = getLetterboxRatio((Vector2) {VIEW_WIDTH, VIEW_HEIGHT});

        BeginTextureMode(render_texture);
        ClearBackground(BLACK);

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

        SetWindowOpacity(window_opacity);

        if (!IsWindowFocused())
            window_opacity = 0.5f;
        else
            if (!IsKeyDown(KEY_ESCAPE)) {
                window_opacity = 1.0f;
            }
            

        if (IsKeyDown(KEY_ESCAPE)) 
            window_opacity -= 0.08f;

        if (window_opacity <= 0) {
            game_end = 1;
        }
    }

    UnloadImage(window_icon);
    UnloadRenderTexture(render_texture);
    CloseWindow();
    exit (EXIT_SUCCESS);
}
