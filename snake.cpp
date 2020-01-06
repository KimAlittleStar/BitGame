#include "snake.h"
#include <QDateTime>

Snake::Snake()
{
    food.x = 0;
    food.y = 0;
    srand(QDateTime::currentDateTime().toSecsSinceEpoch()&0xFFFF);
    snake[0] = {0,0};
    snake[1] = {1,0};
    snake[2] = {2,0};
    createdFood();
    updateSnake();
}

char* Snake::whenUpPress()
{
    K_INFOMATION("press up,line %d\n",__LINE__);

    head = (head+(sizeof(snake)/(sizeof(snake[0]))-1))%(sizeof(snake)/sizeof(snake[0]));
    snake[head] = snake[(head+1)%(sizeof(snake)/sizeof(snake[0]))];
    snake[head].y= (snake[head].y+BitGame::poix-1)%BitGame::poix;
    if(eatFood() == true)
    {
        lengh++;
        if(static_cast<unsigned int>(lengh)  < (BitGame::poix*BitGame::poix))
        {
            createdFood();
        }

    }
    updateSnake();
    K_INFOMATION("head=%d,x = %d,y = %d\n",head,snake[head].x,snake[head].y);
    return BitGame::whenUpPress();
}
char* Snake::whenDownPress()
{
    K_INFOMATION("press down,line %d\n",__LINE__);
    head = (head+(sizeof(snake)/(sizeof(snake[0]))-1))%(sizeof(snake)/sizeof(snake[0]));
    snake[head] = snake[(head+1)%(sizeof(snake)/sizeof(snake[0]))];
    snake[head].y= (snake[head].y+1)%BitGame::poix;
    if(eatFood() == true)
    {
        lengh++;
        if(static_cast<unsigned int>(lengh)  < (BitGame::poix*BitGame::poix))
        {
            createdFood();
        }

    }
    updateSnake();
    return BitGame::whenDownPress();
}
char* Snake::whenLeftPress()
{
    K_INFOMATION("press left,line %d\n",__LINE__);
    head = (head+(sizeof(snake)/(sizeof(snake[0]))-1))%(sizeof(snake)/sizeof(snake[0]));
    snake[head] = snake[(head+1)%(sizeof(snake)/sizeof(snake[0]))];
    snake[head].x= (snake[head].x+BitGame::poix-1)%BitGame::poix;
    if(eatFood() == true)
    {
        lengh++;
        if(static_cast<unsigned int>(lengh)  < (BitGame::poix*BitGame::poix))
        {
            createdFood();
        }

    }
    updateSnake();
    return  BitGame::whenLeftPress();
}
char* Snake::whenRightPress()
{
    K_INFOMATION("press right,line %d\n",__LINE__);
    head = (head+(sizeof(snake)/(sizeof(snake[0]))-1))%(sizeof(snake)/sizeof(snake[0]));
    snake[head] = snake[(head+1)%(sizeof(snake)/sizeof(snake[0]))];
    snake[head].x= (snake[head].x+1)%BitGame::poix;
    if(eatFood() == true)
    {
        lengh++;
        if(static_cast<unsigned int>(lengh)  < (BitGame::poix*BitGame::poix))
        {
            createdFood();
        }

    }
    updateSnake();
    return  BitGame::whenRightPress();
}

void Snake::updateSnake()
{
    memset(map,0,mapSize);
    for(unsigned int i = 0;i<lengh;i++)
    {
        map[(snake[(i+head)%(sizeof(snake)/sizeof(snake[0]))].y)*BitGame::poix +
                snake[(i+head)%(sizeof(snake)/sizeof(snake[0]))].x] = 1;
    }
    map[food.y*BitGame::poix+food.x] = 1;
}
bool Snake::checkOut()
{
    for(unsigned int i = 0;i<lengh;i++)
    {
        for(unsigned int j = i+1;j<lengh;j++)
            if((snake[(i+head)%(sizeof(snake)/sizeof(snake[0]))].x ==
                snake[(j+head)%(sizeof(snake)/sizeof(snake[0]))].x)
                    &&
                    (snake[(i+head)%(sizeof(snake)/sizeof(snake[0]))].y ==
                     snake[(j+head)%(sizeof(snake)/sizeof(snake[0]))].y) )
                return  false;
    }
    return  true;
}
bool Snake::eatFood()
{
    return (food.x == snake[head].x && food.y == snake[head].y );
}

void Snake::createdFood()
{
    while(checkFood() == true)
    {
        food.x = (rand()%BitGame::poix);
        food.y = (rand()%BitGame::poix);
    }

}

bool Snake::checkFood()
{
    for(unsigned int i = 0;i<lengh;i++)
    {
        if(food.x == snake[(head+i)%(sizeof(snake)/sizeof(snake[0]))].x &&
                food.y == snake[(head+i)%(sizeof(snake)/sizeof(snake[0]))].y)
            return true;
    }
    return  false;
}
