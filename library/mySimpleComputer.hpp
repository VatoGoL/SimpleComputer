#pragma once
#include "scRegistr.hpp"
#include "scMemory.hpp"
#include "scTerm.hpp"

class SimpleComputer {
public:
    Registr *registr;
    Memory *memory;
    Term *terminal;

    void Start ( void );

    SimpleComputer();
    virtual ~SimpleComputer();
};