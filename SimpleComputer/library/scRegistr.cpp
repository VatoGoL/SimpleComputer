#include "scRegistr.hpp"

int Registr::regInit(){
    flags = 0b0;
    flags = flags | TACT;
    return 1;
}
int Registr::regSet(int registr, int value){
    if(value < 0 || value > 1){ // 
        return 0;
    }

    bool On; //Во что установить флаг
    if(value == 1){On = true;} //В значение "1"
    else{On = false;} //В значение "0"

    switch (registr)
    {
    case 1:
        if(On == true){
            flags = flags | OVERFLOW; //в 1
            break;
        }
        flags = flags & (~OVERFLOW); //иначе в 0
        break;
    case 2:
        if(On == true){
            flags = flags | ERR_NULL; //в 1
            break;
        }
        flags = flags & (~ERR_NULL); //иначе в 0
        break;
    case 3:
        if(On == true){
            flags = flags | ERR_BORDER; //в 1
            break;
        }
        flags = flags & (~ERR_BORDER); //иначе в 0
        break;
    case 4:
        if(On == true){
            flags = flags | TACT; //в 1
            break;
        }
        flags = flags & (~TACT); //иначе в 0
        break;
    case 5:
        if(On == true){
            flags = flags | ERR_COMMAND; //в 1
            break;
        }
        flags = flags & (~ERR_COMMAND);//иначе в 0
        break;
    default:
        return 0;
        break;
    }
    return 1;
}
int Registr::regGet(int registr, int *value){
    switch (registr) //получаем значчение регистра
    {
    case 1:
        *value = flags & OVERFLOW; 
        break;
    case 2:
        *value = flags & ERR_NULL;
        break;
    case 3:
        *value = flags & ERR_BORDER;
        break;
    case 4:
        *value = flags & TACT;
        break;
    case 5:
        *value = flags & ERR_COMMAND;
        break;
    default:
        return 0;
        break;
    }
    return 1;
}

Registr::Registr(){
    regInit();
}
Registr::~Registr(){}

int Registr::flags = 0b0;