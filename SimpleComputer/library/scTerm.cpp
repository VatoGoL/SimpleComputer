#include "scTerm.hpp"

int Term::mt_clrscr( void ){
    string str = "\E[H\E[J";
    cout << str; //Очистка экрана
    return 0;
}
int Term::mt_gotoXY(int rows, int cols){
    printf("\E[%d;%df", rows, cols); //устанавнивает курсов в позицию строка;колонка
    return 0;
}
int Term::mt_getscreensize(int *rows, int *cols, int fd){
    if(!ioctl(fd, TIOCGWINSZ, &console_size)){
        *rows = console_size.ws_row;
        *cols = console_size.ws_col;
        return 0;
    }
    else{
        printf("\nОшибка: Не получен размер экрана\n");
        return -1;
    }
}
int Term::mt_setscreensize(int rows, int cols, int fd){
    console_size.ws_col = cols;
    console_size.ws_row = rows;
    if(!ioctl(fd, TIOCSWINSZ, console_size)){
        return 0;
    }
    else{
        printf("\nОшибка: Не получилось установить размер экрана\n");
    }
}
int Term::mt_setfgcolor(int color){
    string str;
    switch(color){
        case 1:
            str = "\E[38;2;0;0;0m"; //Чёрный
            break;
        case 2:
            str = "\E[38;2;222;56;43m"; //Красный
            break;
        case 3:
            str = "\E[38;2;44;181;233m"; //Голубой
            break;
        case 4:
            str = "\E[38;2;255;255;0m"; //Жёлтый
            break;
        case 5:
            str = "\E[38;2;255;255;255m"; //Белый
            break;
        default:
            str = "\nВведён неверный цвет фона!\n";
            cout << str;
            return -1;
            break;
    }
    cout << str;
    return 0;
}
int Term::mt_setbgcolor(int color){
    string str;
    switch(color){
        case 1:
            str = "\E[48;2;0;0;0m"; //Чёрный
            break;
        case 2:
            str = "\E[48;2;222;56;43m"; //Красный
            break;
        case 3:
            str = "\E[48;2;44;181;233m"; //Голубой
            break;
        case 4:
            str = "\E[48;2;255;255;0m"; //Жёлтый
            break;
        case 5:
            str = "\E[48;2;255;255;255m"; //Белый
            break;
        default:
            str = "\nВведён неверный цвет фона!\n";
            cout << str;
            return -1;
            break;
    }
    cout << str;
    return 0;
}

Term::Term(){

    fd = open("/dev/tty3",O_WRONLY);
    
    mt_clrscr();
    mt_setbgcolor(DBG_Color);
    mt_setfgcolor(DCC_Color);
    mt_getscreensize(&rows,&cols, 3);
    
}

Term::~Term(){
    close(fd);
}