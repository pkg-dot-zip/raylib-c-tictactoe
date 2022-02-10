#include "raylib.h"

#define BOARD_SIZE (9)
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "TicTacToe"
const int distance = 40;
const int fontSize = 20;

typedef struct {
    char *value;
    int x;
    int y;
} field;

field board[BOARD_SIZE];

void draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Draw board.
    for (int i = 0; i < sizeof(board) / sizeof(board[0]); ++i) {
        DrawRectangleLines(GetScreenWidth() / 2 + board[i].x * distance, GetScreenHeight() / 2 + board[i].y * distance,
                           distance, distance, BLACK);
    }

    // Draw inner values.
    for (int i = 0; i < sizeof(board) / sizeof(board[0]); ++i) {
        field value = board[i];
        const char *textToDraw = value.value;
        const Vector2 textSize = MeasureTextEx(GetFontDefault(), textToDraw, fontSize, 1);
        DrawText(textToDraw, GetScreenWidth() / 2 + value.x * distance + textSize.x / 2,
                 GetScreenHeight() / 2 + value.y * distance + textSize.y, fontSize, BLACK);
    }

    EndDrawing();
}

void update(float deltaTime) {
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = GetMousePosition();

        for (int i = 0; i < sizeof(board) / sizeof(board[0]); ++i) {
            field value = board[i];
            Rectangle rect = {GetScreenWidth() / 2 + value.x * distance, GetScreenHeight() / 2 + value.y * distance,
                              distance, distance};
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

    // Init board.
    for (int x = 0; x < BOARD_SIZE / 3; ++x) {
        for (int y = 0; y < BOARD_SIZE / 3; ++y) {
            char *text = "h";
            field value = {text, x, y};
            board[y * 3 + x] = value;
        }
    }
}

int deInit() {
    CloseWindow();
    return 0;
}

int main(void) {
    init();

    while (!WindowShouldClose()) {
        draw();
        update(GetFrameTime());
    }

    return deInit();
}
