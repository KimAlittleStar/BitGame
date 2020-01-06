#ifndef SNAKE_H
#define SNAKE_H

#include "bitgame.h"
class Snake : public BitGame
{

public:
    typedef struct
    {
        unsigned char x;
        unsigned char y;
    } Point;
    Snake();
    char* whenUpPress();
    char* whenDownPress();
    char* whenLeftPress();
    char* whenRightPress();
    bool checkOut();

private:
    Point snake[BitGame::poix*BitGame::poix];
    Point food;

    unsigned char head = 0;
    unsigned char tail = 3;
    unsigned char lengh = 3;

    void createdFood();
    bool checkFood();
    bool eatFood();
    void updateSnake();
};

#endif // SNAKE_H
