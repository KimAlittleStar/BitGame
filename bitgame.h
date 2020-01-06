#ifndef BITGAME_H
#define BITGAME_H
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#ifndef _DEBUG
#define _DEBUG
#endif
#define USING_BYTE
#define K_PRINT_LINE printf("%s:%d\n", __FILE__, __LINE__)

#define K_PRINT(fmt, ...) qDebug(fmt, ##__VA_ARGS__)

#ifdef _DEBUG
#define K_DEBUG(fmt, ...) K_PRINT(fmt, ##__VA_ARGS__)

#define _DEBUG_LOG
#define _DEBUG_INFO
#define _DEBUG_WARNINR

#else
#define K_DEBUG(fmt, ...)
#endif //ifdef _DEBUG

#if defined(_DEBUG_LOG)
#define K_LOG(TYPE, fmt, ...)        \
    do                               \
    {                                \
        K_PRINT("  >[%s] :", #TYPE); \
        K_PRINT(fmt, ##__VA_ARGS__); \
    } while (0 == 1)
#else
#define K_LOG(TYPE, fmt, ...)
#endif // _DEBUG_LOG

#ifdef _DEBUG_INFO
#define K_INFOMATION(fmt, ...) K_LOG(Info, fmt, ##__VA_ARGS__)
#endif //_DEBUG_INFO

#ifdef _DEBUG_WARNINR
#define K_WARNINR(fmt, ...) K_LOG(Warning, fmt, ##__VA_ARGS__)
#endif //_DEBUG_WARNINR

#define K_ERROR(fmt, ...) K_LOG(Error, fmt, ##__VA_ARGS__)

#define K_SMANAGE_DATA_MIN_BUFF_SIZE ((K_FRAME_DATA_MAX_SIZE + 9) * 2)
class BitGame
{
public:
    enum BitGame_LAST
    {
        KEY_NONE,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
    };
    static const int poix = 16;
    BitGame();
    virtual ~BitGame();
    virtual char* getMap(unsigned char * width,unsigned char* height);
    virtual char* whenUpPress();
    virtual char* whenDownPress();
    virtual char* whenLeftPress();
    virtual char* whenRightPress();
    virtual char* whenTimeOut(void);
protected:
    char* map = nullptr;
    size_t mapSize = 0;
    char* getmalloc(int px = 16);
    BitGame_LAST last = KEY_NONE;
};

#endif // BITGAME_H
