#include <raylib.h>
#include <raymath.h>
#include "Data/Game Configuration.h"


void draw(RenderTexture2D render_texture, Color clear_color, scene_t* scene, float delta);
void render(RenderTexture2D render_texture, Color clear_color, unsigned int render_width, unsigned int render_height);

int main()
{
    InitWindow( (int)VIEWPORT_WIDTH, (int)VIEWPORT_HEIGHT, "Better Sonic The Hedgehog");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize( (int)VIEWPORT_WIDTH, (int)VIEWPORT_HEIGHT);
    SetExitKey(189);

    RenderTexture2D render_texture = LoadRenderTexture(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    SetTextureFilter(render_texture.texture, TEXTURE_FILTER_TRILINEAR);
    
    InitAudioDevice();
    SetTargetFPS((int)FRAMERATE);

    Image window_icon = LoadImageFromMemory(".png", bettersonic_icon_png, BETTER_SONIC_ICON_BYTE_SIZE);
    SetWindowIcon(window_icon);

    float window_opacity = 1.0f;
    unsigned int game_end = 0;


    instaniate_scenes();
    change_scene(sega_splash_screen);


    while (!game_end)
    {
        game_end = (unsigned int)WindowShouldClose();
        draw(render_texture, BLACK, current_scene, GetFrameTime());
        render(render_texture, BLACK, VIEW_WIDTH, VIEW_HEIGHT);
        

        if (!IsWindowFocused()) {
            if (window_opacity != 0.5f) {
                window_opacity = 0.5f;
                SetWindowOpacity(window_opacity);
            }
                
        }    
        else if (IsWindowFocused()) {
            if (!IsKeyDown(KEY_ESCAPE)) {
                if (window_opacity != 1.0f) {
                    window_opacity = 1.0f;
                    SetWindowOpacity(window_opacity);
                }
            }
        }
        
        /* Buggy. Don't use.
        if (IsKeyDown(KEY_F4))
            ToggleFullscreen();
        */
        
            
        if (IsKeyDown(KEY_ESCAPE)) {
            window_opacity -= 0.08f;
            SetWindowOpacity(window_opacity);
        }

        if (window_opacity <= 0) {
            game_end = 1;
        }
    }

    change_scene(NULL);
    UnloadImage(window_icon);
    UnloadRenderTexture(render_texture);
    CloseWindow();
    return 0;
}

void draw(RenderTexture2D render_texture, Color clear_color, scene_t *scene, float delta)
{
    BeginTextureMode(render_texture);
        ClearBackground(clear_color);
        if (scene)
            (scene->update)(delta);

        if (isInDebugMode()) {
            DrawFPS(0, 0);
        }
    EndTextureMode();
}

void render(RenderTexture2D render_texture, Color clear_color, unsigned int render_width, unsigned int render_height)
{
    float scale = getLetterboxRatio((Vector2) { (float)render_width, (float)render_height});

    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            render_texture.texture,
            (Rectangle) {0.0f, 0.0f, 
                (float)render_texture.texture.width, (float)-render_texture.texture.height},

            (Rectangle) { (GetScreenWidth() - ((float)render_width * scale)) * 0.5f, 
                (GetScreenHeight() - ((float)render_height * scale)) * 0.5f,
                    (float)render_width* scale, (float)render_height* scale},

            (Vector2) {0, 0}, 0.0f, WHITE
        );
    EndDrawing();
}
