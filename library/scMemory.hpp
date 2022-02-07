#pragma once
#include "stdio.h"
#include "scRegistr.hpp"

class Memory {

private:
    static const int memory_size = 100;
    int memory[memory_size];
    static const int command_size = 13; //12 + 1
    int command_list[command_size] = 
    {
        10,11, //Операции ввода/вывода
        20,21, //Операции загрузки/выгрузки в аккумулятор
        30,31,32,33, //Арифметческие операции
        40,41,42,43, //Операции передачи управления
        51 //пользовательская функция
    }; 
    #define MAX_COMMAND_ODERAND 0b10000000

public: 
    Registr *reg;

    int memoryInit();
    int memorySet(int adress, int value);
    int memoryGet(int adress, int *value);
    int memorySave(char *filename);
    int memoryLoad(char *filename);
    int memoryShow(); //временная функция

    int commandEncode(int command, int operand, int *value);
    int commandDecode(int value, int *command, int *operand);

    Memory();

    virtual ~Memory();
};