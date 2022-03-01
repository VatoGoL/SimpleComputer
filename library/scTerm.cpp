#include "scTerm.hpp"

int Term::mt_clrscr( void ){
    string str = "\E[H\E[J";
    write(fd,&str[0],str.size()); //Очистка экрана
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
            write(fd,&str[0],str.size());
            return -1;
            break;
    }
    write(fd,&str[0],str.size());
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
            write(fd,&str[0],str.size());
            return -1;
            break;
    }
    write(fd,&str[0],str.size());
    return 0;
}

void Term::Print_Memory(Registr *registr, Memory *memory){
    int value = 0;
    for(int i = 0; i < 10; i++){
        Term::mt_gotoXY(i+2,2);
        printf(" ");
        for(int j = 0; j < 10; j++){
            memory->memoryGet(i*10+j,&value,registr); 
            if(value >> 14 == 0){
                printf("+");
            }
            else {
                printf(" ");
            }
            printf("%5d ", value);
        }
    }
}

void Term::Print_Flags(Registr *registr){
    mt_gotoXY(11, 2*cols/3+13);
    int value;
    registr->regSet(3,1);
    for(int i = 0; i < registr->flags_count; i++){
        registr->regGet(i+1, &value);
        if(value > 0){
            printf(" 1 ");
        }
        else{
            printf(" 0 ");
        }
    }
}
void Term::Print_HelpKeys( void ){
    mt_gotoXY(15, cols/2+11);
    printf("l   - Load");
    mt_gotoXY(16, cols/2+11);
    printf("s   - Save");
    mt_gotoXY(17, cols/2+11);
    printf("r   - Run");
    mt_gotoXY(18, cols/2+11);
    printf("t   - Step");
    mt_gotoXY(19, cols/2+11);
    printf("i   - Reset");
    mt_gotoXY(20, cols/2+11);
    printf("F5  - Accumulator");
    mt_gotoXY(21, cols/2+11);
    printf("F6  - InstructionCounter");
}

Term::Term( Registr *registr, Memory *memory ){

    fd = open("/dev/tty3",O_WRONLY);
    string str;
    //mt_setscreensize(WIDTH,HEIGH,fd);
    mt_clrscr();
    mt_setbgcolor(t_WHITE);
    mt_setfgcolor(t_BLACK);
    mt_getscreensize(&rows,&cols, 3);
    
    //Рисуем рамку для вывода памяти
    str = "\u250c";
    write(fd,&str[0],str.size());//левый верхний угол
    for(int i = 0; i < cols/3 - 1; i++){
        str = "\u2500";
        write(fd,&str[0],str.size());//верх
    }

    str = "MEMORY";
    write(fd,&str[0],str.size());

    for(int i = 0; i < cols/3; i++){
        str = "\u2500";
        write(fd,&str[0],str.size());
    }

    str = "\u2510";
    write(fd,&str[0],str.size()); // правый верхний угол

    
    for(int i = 0; i < 10; i++){
        mt_gotoXY(i+2,0);
        printf("\u2502"); // левый край
    }
    
    printf("\n\u2514"); //левый нижний угол

    for(int i = 0; i < 10; i++){
        mt_gotoXY(i+2,2*cols/3+7);
        printf("\u2502"); //правый край
    }

    mt_gotoXY(10+2,2*cols/3+7);
    printf("\u2518"); //правый нижний угол

    mt_gotoXY(10+2,2);
    for(int i = 0; i < 2*cols/3+5; i++){
        printf("\u2500"); //горизонтальная нижняя линия
    }
    //Рисуем рамку для вывода памяти

    //Рисуем рамку для Accumulator 
    mt_gotoXY(0, 2*cols/3+8);
    printf(" \u250C");
    for(int i = 0; i < 5; i++){
        printf("\u2500");
    }
    printf("Accumulator");
    for(int i = 0; i < 4; i++){
        printf("\u2500");
    }
    printf("\u2510");
    mt_gotoXY(2, 2*cols/3+30); // |
    printf("\u2502");
    mt_gotoXY(3, 2*cols/3+30); // угол правый нижний
    printf("\u2518");
    mt_gotoXY(2, 2*cols/3+9); 
    printf("\u2502");
    mt_gotoXY(3, 2*cols/3+9);
    printf("\u2514");
    mt_gotoXY(3, 2*cols/3+10);
    for(int i = 0; i < 20; i++){
        printf("\u2500");
    }

    //Рисуем рамку для InstructionCounter
    mt_gotoXY(4, 2*cols/3+8);
    printf(" \u250C");
    printf("\u2500InstructionCounter\u2500");
    printf("\u2510");
    mt_gotoXY(5, 2*cols/3+9);
    printf("\u2502");
    mt_gotoXY(5, 2*cols/3+30);
    printf("\u2502");
    mt_gotoXY(6, 2*cols/3+9);
    printf("\u2514");
    for(int i = 0; i < 20; i++){
        printf("\u2500");
    }
    printf("\u2518");

    //Рисуем рамку для Operation
    mt_gotoXY(7, 2*cols/3+8);
    printf(" \u250C");
    for(int i = 0; i < 6; i++){
        printf("\u2500");    
    }
    printf("Operation");
    for(int i = 0; i < 5; i++){
        printf("\u2500");    
    }
    printf("\u2510");
    mt_gotoXY(8, 2*cols/3+9);
    printf("\u2502");
    mt_gotoXY(8, 2*cols/3+30);
    printf("\u2502");
    mt_gotoXY(9, 2*cols/3+9);
    printf("\u2514");
    for(int i = 0; i < 20; i++){
        printf("\u2500");
    }
    printf("\u2518");

    //Рисуем рамку для Flags
    mt_gotoXY(10, 2*cols/3+8);
    printf(" \u250C");
    for(int i = 0; i < 8; i++){
        printf("\u2500");    
    }
    printf("Flags");
    for(int i = 0; i < 7; i++){
        printf("\u2500");    
    }
    printf("\u2510");
    mt_gotoXY(11, 2*cols/3+9);
    printf("\u2502");
    mt_gotoXY(11, 2*cols/3+30);
    printf("\u2502");
    mt_gotoXY(12, 2*cols/3+9);
    printf("\u2514");
    for(int i = 0; i < 20; i++){
        printf("\u2500");
    }
    printf("\u2518");

    //рисуем рамку для больших цифр)
    mt_gotoXY(13, 0);
    printf("\u250C");
    for(int i = 0; i < cols/2+5; i++){
        printf("\u2500");
    }
    printf("\u2510");
    for(int i = 0; i < 10; i++){
        mt_gotoXY(14+i, 0);
        printf("\u2502");
    }
    mt_gotoXY(24, 0);
    printf("\u2514");
    for(int i = 0; i < cols/2+5; i++){
        printf("\u2500");
    }
    printf("\u2518");
    for(int i = 0; i < 10; i++){
        mt_gotoXY(14+i, cols/2+7);
        printf("\u2502");
    }

    //Рисуем рамку для кнопок-подсказок
    mt_gotoXY(13, cols/2+9);
    printf("\u250CKeys:");
    for(int i = 0; i < cols/4+6; i++){
        printf("\u2500");
    }
    printf("\u2510");
    for(int i = 0; i < 10; i++){
        mt_gotoXY(14+i, cols/2+9);
        printf("\u2502");
    }
    mt_gotoXY(24, cols/2+9);
    printf("\u2514");
    for(int i = 0; i < cols/4+11; i++){
        printf("\u2500");
    }
    printf("\u2518");
    for(int i = 0; i < 10; i++){
        mt_gotoXY(14+i, cols/2+9+cols/4+12);
        printf("\u2502");
    }

    Print_Memory(registr,memory);
    Print_Flags(registr);
    Print_HelpKeys();


    mt_gotoXY(26, 0);
    
}

Term::~Term(){
    close(fd);
}