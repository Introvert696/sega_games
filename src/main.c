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

Sprite *player;

int player_pos_x = 144;
const int player_pos_y = 200;
int player_vel_x = 0;
const int player_width = 32;
const int player_height = 8;
const int player_speed = 3;

// отскоки или движение шарика
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

    // проверка столкновение
    if (ball_pos_x < player_pos_x + player_width && ball_pos_x + ball_width > player_pos_x)
    {
        if (ball_pos_y < player_pos_y + player_height && ball_pos_y + ball_height >= player_pos_y)
        {
            ball_pos_y = player_pos_y - ball_height - 1;
            ball_vel_y = -ball_vel_y;
        }
    }

    // движение шарика
    ball_pos_x += ball_vel_x;
    ball_pos_y += ball_vel_y;

    SPR_setPosition(ball, ball_pos_x, ball_pos_y); // устанавливаем позицию
}

// слушатель для контроллера

// joy - контроллер JOY_1 - 8  это джостик
// changed - было ли изменено состаяние за последний кадр
//  state - состояние 1 если нажата,  0 если отпущена

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_RIGHT)
        {
            player_vel_x = player_speed;
        }
        else if (state & BUTTON_LEFT)
        {
            player_vel_x = -player_speed;
        }
        else
        {
            if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT))
            {
                player_vel_x = 0;
            }
        }
    }
}

void positionPlayer()
{
    player_pos_x += player_vel_x;

    // ограничение что бы мы не вышли за рамки экрана
    if (player_pos_x < LEFT_EDGE)
        player_pos_x = LEFT_EDGE;
    if (player_pos_x + player_width > RIGHT_EDGE)
        player_pos_x = RIGHT_EDGE - player_width;

    // устанавливаем позицию игрока
    SPR_setPosition(player, player_pos_x, player_pos_y);
}

int main()
{
    JOY_init();                                      // инициализируем джостик
    JOY_setEventHandler(&myJoyHandler);              // передаем функцию которая будет слушать нажатия джостика
    VDP_loadTileSet(bgtile.tileset, 1, DMA);         // загрузили тайлы в 1 индекс
    PAL_setPalette(PAL1, bgtile.palette->data, DMA); // установили цвет

    // VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 1), 2, 2); // поместили тайл на экран
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 1), 0, 0, 40, 30);

    SPR_init();                                                                                    // инициализируем движок спрайтов
    ball = SPR_addSprite(&imgball, ball_pos_x, ball_pos_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));      // добавляем стпрайт шарика
    player = SPR_addSprite(&paddle, player_pos_x, player_pos_y, TILE_ATTR(PAL1, 0, FALSE, FALSE)); // добавляем игрока

    while (1)
    {
        moveBall();
        positionPlayer(); // обновляем позицию игрока
        SPR_update();     // обновляем спрайты
        SYS_doVBlankProcess();
    }
    return (0);
}
