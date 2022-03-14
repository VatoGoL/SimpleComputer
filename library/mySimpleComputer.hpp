#pragma once
#include "ScreenDrawer.hpp"

class SimpleComputer {
private:
    ScreenDrawer *mainScreen;
    
public:
    
    

    void Start ( void );

    SimpleComputer();
    virtual ~SimpleComputer();
};