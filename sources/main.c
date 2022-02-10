#include "raylib.h"

#define BOARD_SIZE (9)
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "TicTacToe"

Texture2D texture;
const int distance = 40;

typedef struct {
    char* value;
    int x;
    int y;
} field;

field board[BOARD_SIZE];

void draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    const int texture_x = GetScreenWidth() / 2 - texture.width / 2;
    const int texture_y = GetScreenHeight() / 2 - texture.height / 2;
    DrawTexture(texture, texture_x, texture_y, WHITE);

    const char* text = "OMG! IT WORKS!";
    const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
    DrawText(text, GetScreenWidth() / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);

    // Draw board.
    for (int i = 0; i < sizeof(board) / sizeof(board[0]); ++i) {
        DrawRectangleLines(GetScreenWidth() / 2 + board[i].x * distance, GetScreenHeight() / 2 + board[i].y * distance, distance, distance, BLACK);
    }

    // Draw inner values.
    for (int i = 0; i < sizeof(board) / sizeof(board[0]); ++i) {
        field value = board[i];
        const char* textToDraw = value.value;
        DrawText(textToDraw, GetScreenWidth() / 2 + value.x * distance, GetScreenHeight() / 2 + value.y * distance, 20, BLACK);
    }

    EndDrawing();
}

void update(float deltaTime) {
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = GetMousePosition();

        for (int i = 0; i < sizeof(board) / sizeof(board[0]); ++i) {
            field value = board[i];
            Rectangle rect = {GetScreenWidth() / 2 + value.x * distance, GetScreenHeight() / 2 + value.y * distance, distance, distance};
            if (CheckCollisionPointRec(pos, rect)) {
                board[i].value = "X";
                // TODO: Switch turn.
            }
        }
    }
}

void init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works.

    for (int x = 0; x < BOARD_SIZE / 3; ++x) {
        for (int y = 0; y < BOARD_SIZE / 3; ++y) {
            char* text = "h";
            field value = {text, x, y};
            board[y * 3 + x] = value;
        }
    }
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
