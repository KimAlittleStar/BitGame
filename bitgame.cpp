#include "bitgame.h"

BitGame::BitGame()
{
    map = getmalloc();
}
BitGame::~BitGame()
{
    if(map != nullptr)
    {
        std::free(map);
        map = nullptr;
    }
}
char* BitGame::getmalloc(int px)
{
    char* ret = nullptr;
#if defined (USING_BYTE)
    mapSize = (sizeof(char)*static_cast<size_t>( px)*static_cast<size_t>( px));
    ret = reinterpret_cast<char*>(malloc(static_cast<size_t>(mapSize)));
    memset(ret,0,mapSize);
#endif
    return  ret;
}
char* BitGame::getMap(unsigned char * width,unsigned char* height)
{
    if(width != nullptr)
        *width = poix;
    if(height != nullptr)
        *height = poix;
    return this->map;
}
char* BitGame::whenUpPress()
{
    last = KEY_UP;
    return this->map;
}
char* BitGame::whenDownPress()
{
    last = KEY_DOWN;
    return this->map;
}
char* BitGame::whenLeftPress()
{
    last = KEY_LEFT;
    return this->map;
}
char* BitGame::whenRightPress()
{
    last = KEY_RIGHT;
    return this->map;
}
char* BitGame::whenTimeOut(void)
{
    switch(last)
    {
    case KEY_UP:
        whenUpPress();
        break;
    case KEY_DOWN:
        whenDownPress();
        break;
    case KEY_LEFT:
        whenLeftPress();
        break;
    case KEY_RIGHT:
        whenRightPress();
        break;
    default:
        break;
    }

    return this->map;
}
