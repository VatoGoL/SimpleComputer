#pragma once
#include "scMemory.hpp"
#include "scRegistr.hpp"
#include "scTerm.hpp"
#include "ScreenDrawer.hpp"
#include "readKey.hpp"

class CPU {
private:
    Registr *registr;
    Memory *memory;
    ScreenDrawer *mainScreen;
public:

    CPU(Registr *reg, Memory *mem, ScreenDrawer *screen);
    int CU (Term *term, ReadKey *readKeys);
    int ALU (int comand, int operand);
};