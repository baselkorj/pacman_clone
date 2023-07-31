#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "game.h"

int random_int(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    srand(time(NULL));

    Player player = {
        .body = {
            .borderColor = DARKGOLD,
            .color = GOLD,
            .size = 20},
        .mouth = {.end = 0, .start = 0, .angle = 0, .stat = MTH_CLOSING},
        .movement = {.position = {.x = screenWidth / 2, .y = screenHeight / 2}, .speed = 5, .direction = DRCT_RIGHT}};

    Pallet pallet = {.position = {random_int(0 + player.body.size, screenWidth - player.body.size), random_int(0 + player.body.size, screenHeight - player.body.size)}};

    Game game = {
        .score = 0,
        .level = 1};

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        char scoreText[30] = {0};

        sprintf(scoreText, "%d", game.score);

        // draw pallet
        DrawCircle(pallet.position.x, pallet.position.y, 5, WHITE);

        // if pallet inside player circle
        if (CheckCollisionPointCircle(pallet.position, player.movement.position, player.body.size - 5))
        {
            pallet.position.x = random_int(0 + player.body.size, screenWidth - player.body.size);
            pallet.position.y = random_int(0 + player.body.size, screenHeight - player.body.size);
            game.score++;
        }

        if (player.mouth.stat == MTH_OPENING)
        {
            player.mouth.angle -= player.movement.speed * 3;

            if (player.mouth.angle <= 0)
            {
                player.mouth.stat = MTH_CLOSING;
            }
        }
        else
        {
            player.mouth.angle += player.movement.speed * 3;

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
            player.movement.position.x += player.movement.position.x < screenWidth - 25 ? player.movement.speed : 0.0f;
        else if (player.movement.direction == DRCT_LEFT)
            player.movement.position.x -= player.movement.position.x > 0 + 25 ? player.movement.speed : 0.0f;
        else if (player.movement.direction == DRCT_UP)
            player.movement.position.y -= player.movement.position.y > 0 + 25 ? player.movement.speed : 0.0f;
        else if (player.movement.direction == DRCT_DOWN)
            player.movement.position.y += player.movement.position.y < screenHeight - 25 ? player.movement.speed : 0.0f;

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(scoreText, 10, 10, 14, WHITE);

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

        DrawCircleSector(player.movement.position, player.body.size + 3, startAngle, endAngle, 0, DARKGOLD);
        DrawCircleSector(player.movement.position, player.body.size, startAngle, endAngle, 0, GOLD);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
