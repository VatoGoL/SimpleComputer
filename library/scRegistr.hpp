#pragma once
#include "stdio.h"

class Registr {
private:
    static int flags;
    #define OVERFLOW 0b00001 // ПЕРЕПОЛНЕНИЕ "П"
    #define ERR_NULL 0b00010 // ОШИБКА ДЕЛЕНИЯ НА НОЛЬ "0"
    #define ERR_BORDER 0b00100 // ВЫХОД ЗА ГРАНИЦЫ ПАМЯТИ "М"
    #define TACT 0b01000 // ИГНОРИРОВАНИЕ ТАКТОВЫХ ИМПУЛЬСОВ "Т"
    #define ERR_COMMAND 0b10000 // УКАЗАНА НЕВЕРНАЯ КОММАНДА "Е"
public:
    int regInit();
    int regSet(int registr, int value);
    int regGet(int registr, int *value);

    Registr();

    virtual ~Registr();
};