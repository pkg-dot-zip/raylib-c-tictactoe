#include "raylib.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "TicTacToe"

Texture2D texture;

void draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
    const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
    DrawTexture(texture, texture_x, texture_y, WHITE);

    const char* text = "OMG! IT WORKS!";
    const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
    DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);

    EndDrawing();
}

void update(float deltaTime) {

}

void init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works
}

int deInit() {
    UnloadTexture(texture);
    CloseWindow();
    return 0;
}

int main(void)
{
    init();

    while (!WindowShouldClose())
    {
        draw();
        update(GetFrameTime());
    }

    return deInit();
}
