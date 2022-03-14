#pragma once
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

using namespace std;

struct consize {
        unsigned short ws_row = 0;         // Количество строк
        unsigned short ws_col = 0;         // Символов в строке
        unsigned short ws_xpixel = 0;      // Размеры символов в пикселях,
        unsigned short ws_ypixel = 0;      // насколько я знаю - не используются.
};

enum term_color {t_BLACK = 1, t_RED, t_BLUE, t_YELLOW, t_WHITE}; //цвета

class Term {
private:
    #define WIDTH 300
    #define HEIGH 300
    consize console_size;
    
public:
    int cols, rows, fd;
    int DBG_Color = t_WHITE;
    int DCC_Color = t_BLACK;

    int mt_clrscr( void );
    int mt_gotoXY( int rows, int cols );
    int mt_getscreensize( int *rows, int *cols, int fd );
    int mt_setscreensize( int rows, int cols, int fd );
    int mt_setfgcolor( int color );
    int mt_setbgcolor( int color );
    /*void Print_Memory (Registr *registr, Memory *memory);
    void Print_Flags (Registr *registr);*/
    void Print_Counter (int value);
    void Print_HelpKeys ( void );


    Term ();
    virtual ~Term ();
};