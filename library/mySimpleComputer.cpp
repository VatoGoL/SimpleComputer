#include "mySimpleComputer.hpp"

void SimpleComputer::Start( void ){}

SimpleComputer::SimpleComputer(){
    registr = new Registr;
    memory = new Memory;
    terminal = new Term (registr,memory);
    Start();
}
SimpleComputer::~SimpleComputer(){
    delete registr;
    delete memory;
    delete terminal;
}