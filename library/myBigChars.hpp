#pragma once
#include <stdio.h>
#include "scTerm.hpp"

class BigChars {
    #define CHAR_PRINT 'a'
public:

    BigChars();

    int printA (char *str);
    int printBox (int x1, int y1, int w, int h, Term *term);
    int printBigChar (int *letter, int x, int y, int colorCh, int colorBg, Term *term);
    int setBigCharPos (int *big, int x, int y, int value, Term *term);
    int getBigCharPos (int *big, int x, int y, int *value);
    int bigCharWrite (int fd, int **big, int count);
    int bigCharRead (int fd, int **big, int need_count, int *count);

    virtual ~BigChars();
};