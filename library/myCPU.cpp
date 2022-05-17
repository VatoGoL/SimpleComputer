#include "myCPU.hpp"

CPU::CPU(Registr *reg, Memory *mem, ScreenDrawer *screen){
    registr = reg;
    memory = mem;
    mainScreen = screen;
}

//Арифметико логичекое устройство
int CPU::ALU (int comand, int operand){
    int temp, temp_second, temp_result;
    switch(comand){
        //ADD
        case 30:
            temp = mainScreen->get_accumulator();
            temp &= 0b011111111111111;
            memory->memoryGet(operand,&temp_second,registr);
            temp_second &= 0b011111111111111;

            temp_result = temp + temp_second;
            temp_result &= 0b011111111111111;
            temp_result |= 0b100000000000000;
            mainScreen->set_accumulator(temp_result);
        break;
        //SUB
        case 31:
            temp = mainScreen->get_accumulator();
            temp &= 0b011111111111111;
            memory->memoryGet(operand,&temp_second,registr);
            temp_second &= 0b011111111111111;

            temp_result = temp - temp_second;
            temp_result &= 0b011111111111111;
            temp_result |= 0b100000000000000;
            mainScreen->set_accumulator(temp_result);
            
        break;
        //DIVIDE
        case 32:
            temp = mainScreen->get_accumulator();
            temp &= 0b011111111111111;
            memory->memoryGet(operand,&temp_second,registr);
            temp_second &= 0b011111111111111;
            
            temp_result = temp / temp_second;
            temp_result &= 0b011111111111111;
            temp_result |= 0b100000000000000;
            mainScreen->set_accumulator(temp_result);
        break;
        //MUL
        case 33:
            temp = mainScreen->get_accumulator();
            temp &= 0b011111111111111;
            memory->memoryGet(operand,&temp_second,registr);
            temp_second &= 0b011111111111111;

            temp_result = temp * temp_second;
            temp_result &= 0b011111111111111;
            temp_result |= 0b100000000000000;
            mainScreen->set_accumulator(temp_result);
        break;
        //JNEG
        case 41:
            temp = mainScreen->get_accumulator();
            temp &= 0b011111111111111;
            if(temp < 0){
                mainScreen->set_incstructionCounter(operand);
                return 1;
            }
        break;
        //JZ
        case 42:
            temp = mainScreen->get_accumulator();
            temp &= 0b011111111111111;
            if(temp == 0){
                mainScreen->set_incstructionCounter(operand);
                return 1;
            }
        break;
        //CHL
        case 60:
            memory->memoryGet(operand,&temp,registr);
            temp &= 0b011111111111111;
            temp = temp << 1;
            temp &= 0b011111111111111;
            temp |= 0b100000000000000;

            mainScreen->set_accumulator(temp);
        break;
        //SUBC
        case 76:
            memory->memoryGet(operand, &temp, registr);

            temp_second = mainScreen->get_accumulator();
            memory->commandDecode(temp_second,&comand,&operand,registr);
            memory->memoryGet(operand,&temp_second,registr);

            temp &= 0b011111111111111;
            temp_second &= 0b011111111111111;
            
            temp_result = temp - temp_result;
            temp_result &= 0b011111111111111;
            temp_result |= 0b100000000000000;

            mainScreen->set_accumulator(temp - temp_second);
        break;
        default: 
            return -1;
        break;
    }

    return 0;
}
//Контроллер управления
int CPU::CU(int *action){
    bool jump = false;
    int t = mainScreen->get_incstructionCounter();
    int temp, temp_second;
    int value = 0, operand = 0, comand = 0;
    
    //Считываем значение ячейки памяти
    if(memory->memoryGet(t, &value, registr) == -1){
        //Ошибка
        return -1;
    }

    //Декодируем значение
    if(memory->commandDecode(value, &comand, &operand, registr) == -1){
        //Ошибка
        return -1;
    }

    switch (comand)
    {
    //READ
    case 10:
        *action = but_enter;
    break;
    //WRITE
    case 11:
        mainScreen->set_incstructionCounter(operand);
    break;
    //LOAD
    case 20:
        memory->memoryGet(operand, &temp, registr);
        mainScreen->set_accumulator(temp);
    break;
    //STORE
    case 21:
        temp = mainScreen->get_accumulator();
        memory->memorySet(operand,temp,registr);
    break;
    //ADD
    case 30:
        if(ALU(comand,operand) == -1){
            //Ошибка
            return -1;
        }
    break;
    //SUB
    case 31:
        if(ALU(comand,operand) == -1){
            //Ошибка
            return -1;
        }
    break;
    //DIVIDE
    case 32:
        if(ALU(comand,operand) == -1){
            //Ошибка
            return -1;
        }
    break;
    //MUL
    case 33:
        if(ALU(comand,operand) == -1){
            //Ошибка
            return -1;
        }
    break;
    //JUMP
    case 40:
        jump = true;
        mainScreen->set_incstructionCounter(operand);
    break;
    //JNEG
    case 41:
        temp = ALU(comand,operand); 
        if(temp == -1){
            //Ошибка
            return -1;
        }
        else if(temp == 1){
            jump = true;
        }
    break;
    //JZ
    case 42:
        temp = ALU(comand,operand); 
        if(temp == -1){
            //Ошибка
            return -1;
        }
        else if(temp == 1){
            jump = true;
        }
    break;
    //HALT
    case 43:
        return 1;
    break;
    //CHL
    case 60:
        if(ALU(comand,operand) == -1){
            //Ошибка
            return -1;
        }
    break;
    //SUBC
    case 76:
        if(ALU(comand,operand) == -1){
            //Ошибка
            return -1;
        }
    break;

    default:
        return -1;
    break;
    }
    if(jump == false){
        t++;
        mainScreen->set_incstructionCounter(t);
    }
    
    
    return 0;
}


