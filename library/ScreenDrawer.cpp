#include "ScreenDrawer.hpp"
#include "math.h"

ScreenDrawer::ScreenDrawer(){
    term = new Term;
    registr = new Registr;
    memory = new Memory;
    bigChars = new BigChars;
}
ScreenDrawer::~ScreenDrawer(){
    delete term;
    delete registr;
    delete memory;
    delete bigChars;
}

int ScreenDrawer::drawMemory(){
    int value = 0;
    
    for(int i = 0; i < 10; i++){
        term->mt_gotoXY(i+2,4);
        printf(" ");
        for(int j = 0; j < 10; j++){
            memory->memoryGet(i*10+j,&value,registr); 
            term->mt_gotoXY(i+2,5+j*6);

            if(value >> 14 == 0){
                printf("+");
            }
            else {
                printf(" ");
            }

            for(int g = 0; g < 4; g++){
                term->mt_gotoXY(i+2,5+(4-g)+j*6);
                printf( "%x", value%16 );
                value /= 16;
            }
        }
    }
    return 0;
}
int ScreenDrawer::drawFlags(){
    term->mt_gotoXY(11, 2*(term->cols)/3+11);
    int value;
    unsigned char f[6];
    f[0] = 'P', f[1] = '0', f[2] = 'M', f[3] = 'T', f[4] = 'E'; 
    
    for(int i = 0; i < registr->flags_count; i++){
        registr->regGet(i+1, &value);
        if(value > 0){
            printf(" %c ", f[i]);
        }
        else{
            printf(" _ ");
        }
    }
    return 0;
}
int ScreenDrawer::drawBigChars(int value){
    int text[5][2];
    if(value >> 14 == 0){ //смотрим это комманда или нет
        text[0][0] = bcint[16][0]; //если да
        text[0][1] = bcint[16][1];
    }
    else{
        text[0][0] = text[0][1] = 0; //если нет
    }
    for(int i = 1; i < 5; i++){ //смотрим что за цифра в разряде
        text[i][0] = bcint[value%16][0];
        text[i][1] = bcint[value%16][1];

        value /= 16;
    }
    bigChars->printBigChar(text[0],2,14,t_BLACK,t_WHITE,term);
    for(int i = 4; i > 0; i--){
        term->mt_gotoXY( 2+(5-i)*8, 14 );
        bigChars->printBigChar(text[i],2+(5-i)*8,14,t_BLACK,t_WHITE,term);
    }
}
int ScreenDrawer::drawInstructionCounter(){
    term->mt_gotoXY( 5, (2*term->cols/3+3)+15);
    printf("%d", instructionCounter);
    return 0;
}

int ScreenDrawer::drawComputer(){
    instructionCounter = 5;
    memory->memorySet(instructionCounter,0xFFFF,registr);

    bigChars->printBox( 1, 1, 2*term->cols/3, 10, term);                    //Memory
    term->mt_gotoXY(0,term->cols/3);
    printf("Memory");

    bigChars->printBox( (2*term->cols/3+3)+1, 1, term->cols/3-5,1, term);  //Accumulator
    term->mt_gotoXY(0,2*term->cols/3+term->cols/7-1);
    printf("Accumulator");

    bigChars->printBox( (2*term->cols/3+3)+1, 4, term->cols/3-5, 1, term);  //instructionCounter
    term->mt_gotoXY(4,2*term->cols/3+9);
    printf("Instruction Counter");

    bigChars->printBox( (2*term->cols/3+3)+1, 7, term->cols/3-5, 1, term);  //Operation
    term->mt_gotoXY(7,2*term->cols/3+term->cols/7);
    printf("Operation");

    bigChars->printBox( (2*term->cols/3+3)+1, 10, term->cols/3-5, 1, term); //Flags
    term->mt_gotoXY(10,2*term->cols/3+term->cols/7+2);
    printf("Flags");

    bigChars->printBox(1,13,8*5,8,term);                               //BigChars

    bigChars->printBox( (8*5+2)+1, 13, 1.6*term->cols/3+2, 8, term);        //Keys
    term->mt_gotoXY( 13, 2*term->cols/4 );
    printf("Keys:");
    
    drawMemory();
    drawFlags();
    drawInstructionCounter();
    
    
    memory->memoryGet(instructionCounter,&bcValue,registr);
    drawBigChars(bcValue);
    drawInstructionCounter();
    
    /*int value= -1;
    bigChars->getBigCharPos(bcint[0],2,1,&value);
    printf("\nvalue 1 = %d\n", value);
    bigChars->getBigCharPos(bcint[0],3,4,&value);
    printf("\nvalue 2 = %d\n", value);*/

    term->mt_gotoXY(25,1);
}
    