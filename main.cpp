#include <stdio.h>
#include "library/mySimpleComputer.hpp"

int main (){
    Memory *One = new Memory();
    
    //Кодирование комманд
    int value = 0b0;
    int operand = 12;
    int command = 31;

    One->commandEncode(command,operand,&value);
    command = operand = 0;
    printf("\nvalue = %d\n", value);
    printf("\tOperand = %d\n\tCommand = %d", operand, command);
    
    One->commandDecode(value,&command,&operand);
    printf("\nvalue = %d\n", value);
    printf("\tOperand = %d\n\tCommand = %d", operand, command);
    
    //Загрузка/сохранение и загрузка в память
    if(One->memoryLoad("memory_file/memory.dat")){
        One->memoryShow();
    }
    
    if(One->memorySet(10,value)){
        One->memoryShow();
    }
    if(One->memorySave("memory_file/memory.dat")){
        One->memoryLoad("memory_file/memory.dat");
        One->memoryShow();

        One->memorySet(10,0);
        One->memorySave("memory_file/memory.dat");
    }
    //Работа с регистрами
    int reg_temp = 3;
    if(One->reg->regGet(reg_temp,&value)){
        printf("\nRegistr %d = %d", reg_temp, value);
    }
    if(One->reg->regSet(reg_temp,1)){
        One->reg->regGet(reg_temp,&value);
        printf("\nRegistr %d = %d", reg_temp, value);
    }
    return 0;
} //280 строк кода)))