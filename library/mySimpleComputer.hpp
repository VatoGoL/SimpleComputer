#pragma once
#include "readKey.hpp"
#include "ScreenDrawer.hpp"

class SimpleComputer {
private:
    int fd;
    ScreenDrawer *mainScreen;
    
    ReadKey *readKeys;
    Registr *registr;
    Term *term;
    Memory *memory;
public:
    
    void Start ( void );

    SimpleComputer();
    virtual ~SimpleComputer();
};