#pragma once
#include "readKey.hpp"
#include "myCPU.hpp"
#include "ScreenDrawer.hpp"
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>

class SimpleComputer {
private:
    int fd;
    int ignore_imp;
    ScreenDrawer *mainScreen;
    
    ReadKey *readKeys;
    Registr *registr;
    Term *term;
    Memory *memory;
    CPU *cpu;

    itimerval nval, oval;
    
    static bool signlTimer;
    static bool signlUsr;

public:
    
    static void set_signlTimer( bool value );
    static void set_signlUsr( bool value );

    void startTimer( void );

    void Start ( void );

    SimpleComputer();
    virtual ~SimpleComputer();
};


void signalTimer(int signo);    
void signalUsr(int signo);