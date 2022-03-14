#include "mySimpleComputer.hpp"

void SimpleComputer::Start( void ){
    //bChars->printBox(0,0,10,15);
    mainScreen->drawComputer();
    
}

SimpleComputer::SimpleComputer(){
    mainScreen = new ScreenDrawer;
    Start();
}
SimpleComputer::~SimpleComputer(){
    delete mainScreen;
}