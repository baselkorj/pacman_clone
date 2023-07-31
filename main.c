#include "raylib.h"
#include <stdio.h>

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

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        char frameTime[30] = {0};

        sprintf(frameTime, "%lf", GetTime());

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

        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        DrawText(frameTime, 10, 10, 14, BLACK);

        // Draw Pac-Man body (yellow circle)
        DrawCircleSector(playerPosition, radius, 90 + mouthAngle / 2, 495 - mouthAngle, 0, YELLOW);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}