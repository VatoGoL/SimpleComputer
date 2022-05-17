#pragma once
#include "stdio.h"
#include "scRegistr.hpp"

class Memory {

private:
    static const int memory_size = 100;
    int memory[memory_size];
    static const int command_size = 14; //12 + 2
    int command_list[command_size] = 
    {
        10,11, //Операции ввода/вывода
        20,21, //Операции загрузки/выгрузки в аккумулятор
        30,31,32,33, //Арифметческие операции
        40,41,42,43, //Операции передачи управления
        60,76 //пользовательская функция
    }; 
    #define MAX_COMMAND_ODERAND 0b10000000

public: 

    int memoryInit();
    int memorySet(int adress, int value, Registr *reg);
    int memoryGet(int adress, int *value, Registr *reg);
    int memorySave(char *filename);
    int memoryLoad(char *filename);
    int memoryShow(); //временная функция

    int commandEncode(int command, int operand, int *value);
    int commandDecode(int value, int *command, int *operand, Registr *reg);

    Memory();

    virtual ~Memory();
};