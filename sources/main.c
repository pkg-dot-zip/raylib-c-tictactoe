#include "raylib.h"

#define ROW_SIZE (3)
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "TicTacToe"

const int distance = 40;
const int fontSize = 20;
const char *player1 = "o";
const char *player2 = "x";

char *board[ROW_SIZE][ROW_SIZE];

int turn = 0; // 0 for player one & 1 for player two.

void checkIfWon() {
    // Check horizontal.
    for (int i = 0; i < ROW_SIZE; ++i) {

    }
}

void draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Draw board.
    for (int x = 0; x < ROW_SIZE; ++x) {
        for (int y = 0; y < ROW_SIZE; ++y) {
            DrawRectangleLines(GetScreenWidth() / 2 - (ROW_SIZE * (distance / 2)) + x * distance,
                               GetScreenHeight() / 2 + y * distance,
                               distance, distance, BLACK);
        }
    }

    // Draw inner values.
    for (int x = 0; x < ROW_SIZE; ++x) {
        for (int y = 0; y < ROW_SIZE; ++y) {
            const char *textToDraw = board[x][y];
            const Vector2 textSize = MeasureTextEx(GetFontDefault(), textToDraw, fontSize, 1);
            DrawText(textToDraw, GetScreenWidth() / 2 - (ROW_SIZE * (distance / 2)) + x * distance + textSize.x / 2,
                     GetScreenHeight() / 2 + y * distance + textSize.y, fontSize, BLACK);
        }
    }

    EndDrawing();
}

void update(float deltaTime) {
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = GetMousePosition();

        for (int x = 0; x < ROW_SIZE; ++x) {
            for (int y = 0; y < ROW_SIZE; ++y) {
                Rectangle rect = {GetScreenWidth() / 2 - (ROW_SIZE * (distance / 2)) + x * distance,
                                  GetScreenHeight() / 2 + y * distance,
                                  distance, distance};

                if (CheckCollisionPointRec(pos, rect)) {

                    // Check if no move has been made on that field, then set the appropriate player's letter there.
                    if (board[x][y] == " ") {
                        board[x][y] = turn == 0 ? player1 : player2;
                        turn = turn == 0 ? 1 : 0; // Switch turn.
                    }
                }
            }
        }

        checkIfWon();
    }
}

void initBoard() {
    for (int x = 0; x < ROW_SIZE; ++x) {
        for (int y = 0; y < ROW_SIZE; ++y) {
            char *text = " ";
            board[x][y] = text;
        }
    }
}

void init() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    initBoard();
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
