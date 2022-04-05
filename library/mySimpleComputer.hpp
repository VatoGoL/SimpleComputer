#pragma once
#include "readKey.hpp"
#include "ScreenDrawer.hpp"
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

class SimpleComputer {
private:
    int fd;
    ScreenDrawer *mainScreen;

    ReadKey *readKeys;
    Registr *registr;
    Term *term;
    Memory *memory;

    itimerval nval, oval;
    
public:
    
    void startTimer( void );
    void stopTimer( void );

    void Start ( void );

    SimpleComputer();
    virtual ~SimpleComputer();
};