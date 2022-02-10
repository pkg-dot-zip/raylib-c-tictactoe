#include "raylib.h"
#include <stdio.h>

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
int won = 0;

void initBoard();

int checkIfWon(char* pString[ROW_SIZE][ROW_SIZE]) {
    int matches;

    // Check vertical.
    for (int y = 0; y < ROW_SIZE; ++y) {
        matches = 1;
        char *player = pString[0][y];

        if (player == " ") break;

        for (int x = 1; x < ROW_SIZE; ++x) {
            if (pString[x][y] == player) {
                matches++;
                printf("%d, %d ", x, y);
            }
        }

        if (matches == ROW_SIZE) return 1;
    }

    // Check horizontal.
    for (int x = 0; x < ROW_SIZE; ++x) {
        matches = 1;
        char *player = pString[x][0];

        if (player == " ") break;

        for (int y = 1; y < ROW_SIZE; ++y) {
            if (pString[x][y] == player) {
                matches++;
            }
        }

        if (matches == ROW_SIZE) return 1;
    }


    // Check diagonal.
    if (pString[1][1] != " ") {
        char* player = pString[1][1];

        if (pString[0][0] == player && pString[1][1] == player && pString[2][2] == player) return 1;
        if (pString[0][2] == player && pString[1][1] == player && pString[2][0] == player) return 1;
    }

    // Check if all fields are filled.
    int filledFields = 0;
    for (int x = 0; x < ROW_SIZE; ++x) {
        for (int y = 0; y < ROW_SIZE; ++y) {
            if (pString[x][y] != " ") filledFields++;
        }
    }

    if (filledFields == ROW_SIZE * ROW_SIZE) {
        return 1;
    }

    return 0;
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

    // Win screen.
    if (won == 1) {
        const char *text = "Press space to restart!";
        const Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, GetScreenWidth() / 2 - textSize.x / 2, GetScreenHeight() / 2 + textSize.y + 10, 20, BLACK);
    }

    EndDrawing();
}

void update(float deltaTime) {
    if (won == 1) {
        if (IsKeyReleased(KEY_SPACE)) {
            initBoard();
            turn = 0;
            won = 0;
        }
        return;
    }

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

        won = checkIfWon(board);
    }
}

void initBoard() {
    for (int x = 0; x < ROW_SIZE; ++x) {
        for (int y = 0; y < ROW_SIZE; ++y) {
            const char *text = " ";
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
