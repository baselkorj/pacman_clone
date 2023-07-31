#include <raylib.h>

// Extra Colors
#define DARKGOLD \
    CLITERAL(Color) { 179, 142, 0, 255 }

#define BASE_GRID_X 32
#define BASE_GRID_Y 18

// Player Definitions
typedef enum
{
    MTH_OPENING,
    MTH_CLOSING
} MouthStat;

typedef enum
{
    DRCT_RIGHT,
    DRCT_LEFT,
    DRCT_UP,
    DRCT_DOWN
} Direction;

typedef struct
{
    struct
    {
        Vector2 position;
        int speed;
        Direction direction;
    } movement;

    struct
    {
        int angle;
        int start;
        int end;
        MouthStat stat;
    } mouth;

    struct
    {
        Color color;
        Color borderColor;
    } body;
} Player;

typedef struct
{
    bool debug;
    int score;
    int level;
} Game;

typedef struct
{
    Vector2 position;
} Pallet;