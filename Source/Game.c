#include <raylib.h>
#include <raymath.h>
#include "Entities/Scene.h"
#include "Scenes/Scene Manager.h"
#include "Data/Game Configuration.h"
#include "Embedded Assets/Assets.h"
#include "Utilities/Utility.h"

void draw(RenderTexture2D render_texture, Color clear_color, Scene* scene, float delta);
void render(RenderTexture2D render_texture, Color clear_color, const unsigned short render_width, const unsigned short render_height);

int main()
{
    InitWindow( (int)VIEWPORT_WIDTH, (int)VIEWPORT_HEIGHT, "Better Sonic The Hedgehog");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize( (int)VIEWPORT_WIDTH, (int)VIEWPORT_HEIGHT);
    SetExitKey(189);

    RenderTexture2D render_texture = LoadRenderTexture(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    SetTextureFilter(render_texture.texture, TEXTURE_FILTER_POINT);
    
    InitAudioDevice();
    SetTargetFPS((int)FRAMERATE);

    Image window_icon = LoadImageFromMemory(".png", bettersonic_icon_png, BETTER_SONIC_ICON_BYTE_SIZE);
    if (isOperatingSystem(OS_MACOSX) == 0) {
        SetWindowIcon(window_icon);
    }

    float window_opacity = 1.0f;
    unsigned int game_end = 0;


    instaniateScenes();
    changeToScene(sceneSegaSplashScreen);


    while (game_end == 0)
    {
        game_end = (unsigned char)WindowShouldClose();
        draw(render_texture, BLACK, currentScene, GetFrameTime());
        render(render_texture, BLACK, (int)VIEWPORT_WIDTH, (int)VIEWPORT_HEIGHT);
        

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
            window_opacity -= 0.08f * GetFrameTime();
            SetWindowOpacity(window_opacity);
        }

        if (window_opacity <= 0) {
            game_end = 1;
        }
    }

    changeToScene(NULL);
    destroyScenes();
    UnloadImage(window_icon);
    UnloadRenderTexture(render_texture);
    CloseWindow();
    return 0;
}

void draw(RenderTexture2D render_texture, Color clear_color, Scene* scene, float delta)
{
    BeginTextureMode(render_texture);
        ClearBackground(clear_color);
        if (scene)
            (scene->update)(delta);

        if (isInDebugMode()) {
            DrawTextEx(GetFontDefault(), TextFormat("FPS: %i/%.2f", GetFPS(), GetFrameTime()*1000), (Vector2){0, VIEWPORT_HEIGHT - MeasureTextEx(GetFontDefault(), TextFormat("FPS: %i/%.2f", GetFPS(), GetFrameTime()*1000), 12, 2).y}, 12, 2, GREEN);
        }
    EndTextureMode();
}

void render(RenderTexture2D render_texture, Color clear_color, const unsigned short render_width, const unsigned short render_height)
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
