#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    int currentGrid = 800 / BASE_GRID;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    srand(time(NULL));

    Player player = {
        .body = {
            .borderColor = DARKGOLD,
            .color = GOLD},
        .mouth = {.end = 0, .start = 0, .angle = 0, .stat = MTH_CLOSING},
        .movement = {.position = {.x = screenWidth / 2, .y = screenHeight / 2}, .speed = 4, .direction = DRCT_RIGHT}};

    Pallet pallet = {.position = {GetRandomValue(0 + currentGrid * 1.5, screenWidth - currentGrid * 1.5), GetRandomValue(0 + currentGrid * 1.5, screenHeight - currentGrid * 1.5)}};

    Game game = {
        .debug = true,
        .score = 0,
        .level = 1};

    char scoreText[30] = "";
    char levelText[30] = "";
    char fpsText[30] = "";

    // collision map, 1 is collision
    int collisionMap[20][30] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // update score, level, and fps texts
        sprintf(scoreText, "SCORE : %d", game.score);
        sprintf(levelText, "LEVEL : %d", game.level);
        sprintf(fpsText, "FPS\t\t\t: %d", GetFPS());

        // draw pallet
        DrawCircle(pallet.position.x, pallet.position.y, 3, WHITE);

        // if pallet inside player circle
        if (CheckCollisionPointCircle(pallet.position, player.movement.position, currentGrid))
        {
            pallet.position.x = GetRandomValue(0 + currentGrid * 1.5, screenWidth - currentGrid * 1.5);
            pallet.position.y = GetRandomValue(0 + currentGrid * 1.5, screenHeight - currentGrid * 1.5);
            game.score++;
        }

        if (player.mouth.stat == MTH_OPENING)
        {
            player.mouth.angle -= player.movement.speed * 5;

            if (player.mouth.angle <= 0)
            {
                player.mouth.stat = MTH_CLOSING;
            }
        }
        else
        {
            player.mouth.angle += player.movement.speed * 5;

            if (player.mouth.angle >= 105)
            {
                player.mouth.stat = MTH_OPENING;
            }
        }

        if (IsKeyDown(KEY_RIGHT))
            player.movement.direction = DRCT_RIGHT;
        if (IsKeyDown(KEY_LEFT))
            player.movement.direction = DRCT_LEFT;
        if (IsKeyDown(KEY_UP))
            player.movement.direction = DRCT_UP;
        if (IsKeyDown(KEY_DOWN))
            player.movement.direction = DRCT_DOWN;

        if (player.movement.direction == DRCT_RIGHT)
            player.movement.position.x += player.movement.position.x < screenWidth - (currentGrid / 2) ? player.movement.speed : 0.0f;
        else if (player.movement.direction == DRCT_LEFT)
            player.movement.position.x -= player.movement.position.x > (currentGrid / 2) ? player.movement.speed : 0.0f;
        else if (player.movement.direction == DRCT_UP)
            player.movement.position.y -= player.movement.position.y > (currentGrid / 2) ? player.movement.speed : 0.0f;
        else if (player.movement.direction == DRCT_DOWN)
            player.movement.position.y += player.movement.position.y < screenHeight - (currentGrid / 2) ? player.movement.speed : 0.0f;

        BeginDrawing();

        // visualize collision map
        if (game.debug)
        {
            for (int i = 0; i < screenWidth / currentGrid; i++)
            {
                for (int j = 0; j < screenHeight / currentGrid; j++)
                {
                    if (collisionMap[j][i])
                    {
                        DrawRectangle(i * currentGrid, j * currentGrid, currentGrid, currentGrid, CLITERAL(Color){255, 255, 255, 50});
                    }
                }
            }
        }

        // render texts
        DrawText(fpsText, 10, 10, 14, WHITE);
        DrawText(levelText, 10, 30, 14, WHITE);
        DrawText(scoreText, 10, 50, 14, WHITE);

        ClearBackground(BLACK);

        // Draw Pac-Man body (yellow circle)
        int startAngle, endAngle;

        // Calculate start and end angles based on player direction
        if (player.movement.direction == DRCT_RIGHT)
        {
            startAngle = 90 + player.mouth.angle / 2;
            endAngle = 495 - player.mouth.angle;
        }
        else if (player.movement.direction == DRCT_LEFT)
        {
            startAngle = -90 + player.mouth.angle / 2;
            endAngle = 315 - player.mouth.angle;
        }
        else if (player.movement.direction == DRCT_UP)
        {
            startAngle = 180 + player.mouth.angle / 2;
            endAngle = 585 - player.mouth.angle;
        }
        else if (player.movement.direction == DRCT_DOWN)
        {
            startAngle = 0 + player.mouth.angle / 2;
            endAngle = 405 - player.mouth.angle;
        }

        DrawCircleSector(player.movement.position, (currentGrid / 2) - 5, startAngle, endAngle, 0, DARKGOLD);
        DrawCircleSector(player.movement.position, (currentGrid / 2) - 8, startAngle, endAngle, 0, GOLD);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
