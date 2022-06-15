#include "ScreenDrawer.hpp"
#include "math.h"

ScreenDrawer::ScreenDrawer(Registr *reg, Term *ter, Memory *mem){
    term = ter;
    registr = reg;
    memory = mem;
    bigChars = new BigChars;
}
ScreenDrawer::~ScreenDrawer(){
    delete bigChars;
}
int ScreenDrawer::drawMemory(int position){
    int value = 0;
    term->mt_setbgcolor(t_WHITE);
    term->mt_setfgcolor(t_BLACK);
    for(int i = 0; i < 10; i++){
        term->mt_gotoXY(i+2,4);
        printf(" ");
        for(int j = 0; j < 10; j++){
            if((position / 10 == i) && (position % 10 == j)){    
                term->mt_setbgcolor(t_BLACK);
                term->mt_setfgcolor(t_WHITE);      
            }
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

            if((position / 10 == i) && (position % 10 == j)){
                term->mt_setbgcolor(t_WHITE);
                term->mt_setfgcolor(t_BLACK);
            }
        }
    }
    return 0;
}

void ScreenDrawer::drawHelpKeys( void ){
    term->mt_gotoXY(14, term->cols/3+12);
    printf("l   - Load");
    term->mt_gotoXY(15, term->cols/3+12);
    printf("s   - Save");
    term->mt_gotoXY(16, term->cols/3+12);
    printf("r   - Run");
    term->mt_gotoXY(17, term->cols/3+12);
    printf("t   - Step");
    term->mt_gotoXY(18, term->cols/3+12);
    printf("i   - Reset");
    term->mt_gotoXY(19, term->cols/3+12);
    printf("F4  - Set memory");
    term->mt_gotoXY(20, term->cols/3+12);
    printf("F5  - Accumulator");
    term->mt_gotoXY(21, term->cols/3+12);
    printf("F6  - InstructionCounter");

    term->mt_gotoXY(14, term->cols/3+12 + 25);
    printf("f   - flags");
}

int ScreenDrawer::drawFlags(){
    term->mt_gotoXY(11, 2*(term->cols)/3+11);
    int value;
    unsigned char f[5];
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
    printf("%2x", instructionCounter);
    return 0;
}
void ScreenDrawer::set_incstructionCounter(int value){
    if(value > -1 && value < 100){
        instructionCounter = value;
    }
}
int ScreenDrawer::get_incstructionCounter (void){
    return instructionCounter;
}
int ScreenDrawer::drawAccumulator(){
    term->mt_gotoXY( 2, (2*term->cols/3+3)+15);
    printf("%2x", accumulator);
    return 0;
}
void ScreenDrawer::set_accumulator(int value){
    if(value > -1 && value < 32767){
        accumulator = value;   
    }
}
int ScreenDrawer::get_accumulator(void){
    return accumulator;
}
void ScreenDrawer::drawOutput( int value ){
    term->mt_gotoXY( 26, 0);
    printf("Output: %d\n", value);
}
void ScreenDrawer::drawOperation( void ){
    int value = 0, command = 0, operand = 0;
    memory->memoryGet(instructionCounter, &value, registr);
    //value = 0b10100000000;//1280
    term->mt_gotoXY( 8, (2*term->cols/3+3)+12);
    memory->commandDecode(value,&command,&operand, registr);
    registr->regSet(5,0);
    printf("%2x : %2x", command, operand);
}
int ScreenDrawer::drawComputer(){

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
    
    drawMemory(instructionCounter);
    drawFlags();
    drawAccumulator();
    drawInstructionCounter();
    drawHelpKeys();
    drawOperation();
    
    memory->memoryGet(instructionCounter,&bcValue,registr);
    drawBigChars(bcValue);
    drawInstructionCounter();
  
}
    