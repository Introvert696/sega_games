/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include <resources.h>

// границы экрана
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
const int TOP_EDGE = 0;
const int BOTTOM_EDGE = 224;

Sprite *ball;

// переменные для шарика
int ball_pos_x = 100;
int ball_pos_y = 100;
int ball_vel_x = 1;
int ball_vel_y = 1;
int ball_width = 8;
int ball_height = 8;

void moveBall()
{
    // отскоки по оси Х
    if (ball_pos_x < LEFT_EDGE)
    {
        ball_pos_x = LEFT_EDGE;
        ball_vel_x = -ball_vel_x;
    }
    else if (ball_pos_x + ball_width > RIGHT_EDGE)
    {
        ball_pos_x = RIGHT_EDGE - ball_width;
        ball_vel_x = -ball_vel_x;
    }
    // осткоки по оси Y
    if (ball_pos_y < TOP_EDGE)
    {
        ball_pos_y = TOP_EDGE;
        ball_vel_y = -ball_vel_y;
    }
    else if (ball_pos_y + ball_height > BOTTOM_EDGE)
    {
        ball_pos_y = BOTTOM_EDGE - ball_height;
        ball_vel_y = -ball_vel_y;
    }

    // движение шарика
    ball_pos_x += ball_vel_x;
    ball_pos_y += ball_vel_y;

    SPR_setPosition(ball, ball_pos_x, ball_pos_y); // устанавливаем позицию
}

int main()
{
    VDP_loadTileSet(bgtile.tileset, 1, DMA);         // загрузили тайлы в 1 индекс
    PAL_setPalette(PAL1, bgtile.palette->data, DMA); // установили цвет

    // VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 1), 2, 2); // поместили тайл на экран
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 1), 0, 0, 40, 30);

    SPR_init();                                                                 // инициализируем движок спрайтов
    ball = SPR_addSprite(&imgball, 100, 100, TILE_ATTR(PAL1, 0, FALSE, FALSE)); // добавляем стпрайты

    while (1)
    {
        moveBall();
        SPR_update(); // обновляем спрайты
        SYS_doVBlankProcess();
    }
    return (0);
}
