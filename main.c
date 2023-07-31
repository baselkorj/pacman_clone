#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PLDR_RIGHT 0
#define PLDR_LEFT 1
#define PLDR_UP 2
#define PLDR_DOWN 3

#define DARKGOLD \
    CLITERAL(Color) { 179, 142, 0, 255 }

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    Vector2 playerPosition = {screenWidth / 2, screenHeight / 2};

    float radius = 20.0f;
    int mouthAngle = 90;

    bool mouthOpening = true;

    int playerSetDirection = PLDR_RIGHT;

    int score = 0;

    srand(time(NULL));

    Vector2 palletPosition = {rand() % screenWidth, rand() % screenHeight};

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        char scoreText[30] = {0};

        sprintf(scoreText, "%d", score);

        // draw pallet
        DrawCircle(palletPosition.x, palletPosition.y, 5, WHITE);

        // if pallet inside player circle
        if (CheckCollisionPointCircle(palletPosition, playerPosition, 25))
        {
            palletPosition.x = rand() % screenWidth;
            palletPosition.y = rand() % screenHeight;
            score++;
        }

        if (mouthOpening)
        {
            mouthAngle -= 15;

            if (mouthAngle <= 0)
            {
                mouthOpening = false;
            }
        }
        else
        {
            mouthAngle += 15;

            if (mouthAngle >= 105)
            {
                mouthOpening = true;
            }
        }

        if (IsKeyDown(KEY_RIGHT))
            playerSetDirection = PLDR_RIGHT;
        if (IsKeyDown(KEY_LEFT))
            playerSetDirection = PLDR_LEFT;
        if (IsKeyDown(KEY_UP))
            playerSetDirection = PLDR_UP;
        if (IsKeyDown(KEY_DOWN))
            playerSetDirection = PLDR_DOWN;

        if (playerSetDirection == PLDR_RIGHT)
            playerPosition.x += playerPosition.x < screenWidth - 25 ? 4.0f : 0.0f;
        else if (playerSetDirection == PLDR_LEFT)
            playerPosition.x -= playerPosition.x > 0 + 25 ? 4.0f : 0.0f;
        else if (playerSetDirection == PLDR_UP)
            playerPosition.y -= playerPosition.y > 0 + 25 ? 4.0f : 0.0f;
        else if (playerSetDirection == PLDR_DOWN)
            playerPosition.y += playerPosition.y < screenHeight - 25 ? 4.0f : 0.0f;

        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawText(scoreText, 10, 10, 14, LIGHTGRAY);

        // Draw Pac-Man body (yellow circle)
        int startAngle, endAngle;

        // Calculate start and end angles based on player direction
        if (playerSetDirection == PLDR_RIGHT)
        {
            startAngle = 90 + mouthAngle / 2;
            endAngle = 495 - mouthAngle;
        }
        else if (playerSetDirection == PLDR_LEFT)
        {
            startAngle = -90 + mouthAngle / 2;
            endAngle = 315 - mouthAngle;
        }
        else if (playerSetDirection == PLDR_UP)
        {
            startAngle = 180 + mouthAngle / 2;
            endAngle = 585 - mouthAngle;
        }
        else if (playerSetDirection == PLDR_DOWN)
        {
            startAngle = 0 + mouthAngle / 2;
            endAngle = 405 - mouthAngle;
        }

        DrawCircleSector(playerPosition, 23, startAngle, endAngle, 0, DARKGOLD);
        DrawCircleSector(playerPosition, radius, startAngle, endAngle, 0, GOLD);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
