#include "myBigChars.hpp"

BigChars::BigChars (){}
BigChars::~BigChars(){}


int BigChars::printA(char *str){
    printf("\E(0%s\E(B", str);
}

int BigChars::printBox (int x1, int y1, int w, int h, Term *term){
    if(x1 < 0 || y1 < 0){ return -1;}
    else if(x1 + w > term->cols - 2 || y1 + h > term->rows - 2 ){return -1;}

    term->mt_gotoXY(y1,x1);
    
    printf("\u250c");
    for(int i = 0; i < w; i++){
        printf("\u2500");
    }
    printf("\u2510");

    for(int i = 0; i < h; i++){
        term->mt_gotoXY(y1+i+1,x1);
        printf("\u2502");
    }
    term->mt_gotoXY(y1+h+1,x1);
    printf("\u2514");

    for(int i = 0; i < h; i++){
        term->mt_gotoXY(y1+i+1,x1+w+1);
        printf("\u2502");
    }
    
    term->mt_gotoXY(y1+h+1,x1+1);
    for(int i = 1; i < w+1; i++){
        printf("\u2500");
    }
    term->mt_gotoXY(y1+h+1,x1+w+1);
    printf("\u2518\n");

    return 0;
}
int BigChars::printBigChar (int *letter, int x, int y, int colorCh, int colorBg, Term *term){
    if(y > term->rows || y < 0 || x > term->cols || x < 0){
        return -1;
    }

    term->mt_gotoXY(y,x);
    term->mt_setfgcolor(colorCh);
    term->mt_setbgcolor(colorBg);
    printf("\E(0");
    int One = letter[0], Two = letter[1];
    int Mask = 0b1;
    for(int i = 0; i < 4*8; i++){
        if(i % 8 == 0 && i != 0){
            term->mt_gotoXY(y+(i/8),x);
        }
        if(One & Mask == 0b1){
            printf("%c", CHAR_PRINT);
        }
        else {
            printf(" ");
        }
        One = One >> 1;
    }
    
    term->mt_gotoXY(y+(4),x);
    for(int i = 0; i < 4*8; i++){
        if(i % 8 == 0 && i != 0){
            term->mt_gotoXY(y+(4+i/8),x);
        }
        if(Two & Mask == 1){
            printf("%c", CHAR_PRINT);
        }
        else {
            printf(" ");
        }
        Two >>= 1;
    }
    printf("\E(B");

    return 0;
}
int BigChars::setBigCharPos (int *big, int x, int y, int value, Term *term){

    if(x > 7 || x < 0 || y > 7 || y < 0){
        return -1;
    }
    if(value < 0 || value > 1){
        return -1;
    }

    int mask = 0b1;
    

    term->mt_gotoXY(y,x);

    mask <<= x;
    mask <<= y%4*8;
    if( y < 5 ){
        if( value == 1){
            big[0] |= mask; 
        }
        else {
            big[0] &= (~mask);
        }
    }
    else{
        if( value == 1){
            big[1] |= mask; 
        }
        else {
            big[1] &= (~mask);
        }
    }
   
}
int BigChars::getBigCharPos (int *big, int x, int y, int *value){
    if(x > 7 || x < 0 || y > 7 || y < 0){
        return -1;
    }
    
    int mask = 0b1;

    mask <<= x;
    mask <<= y%4*8;
    int t_mask = mask;
    if( y < 5 ){
        *value = big[0] & mask;
    }
    else{
        *value = big[1] & mask;
    }
    return 0;
}
int BigChars::bigCharWrite (int fd, int **big, int count){
    int error = write(fd,&count,sizeof(count));
    
    if(error == -1){
        return -1;
    }

    error = write(fd,big,count*sizeof(int) * 2);

    if(error == -1){
        return -1;
    }

    return 0;
}
int BigChars::bigCharRead (int fd, int **big, int need_count, int *count){
    int error = read(fd,count,sizeof(int));
    
    if(error == -1 || error != sizeof(int)){
        return -1;
    }

    error = read(fd,big,(*count)*sizeof(int) * 2);

    if(error == -1){
        return -1;
    }
    if(*count != need_count){
        return -1;
    }
    return 0;
}