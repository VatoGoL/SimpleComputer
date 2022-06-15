#include "library/scMemory.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

#define N 100

using namespace std;

//функция преобразования строки в число
int str_to_int(const char *str, int razrad){
    int degree = -1;
    int result = 0;
    int znak = 0;
    if(str[0] == '-'){
        znak = -1;
        degree--;
    }
    else if(str[0] == '+'){
        znak = 1;
        degree--;
    }
    for(int i = 0; str[i] != '\0'; i++){
        degree++;
    }
    
    for(int i = (znak == 0 ? 0 : 1); str[i] != '\0'; i++){
        switch(str[i]){
            case '1':
                result += 1*pow(razrad,degree);
            break;
            case '2':
                result += 2*pow(razrad,degree);
            break;
            case '3':
                result += 3*pow(razrad,degree);
            break;
            case '4':
                result += 4*pow(razrad,degree);
            break;
            case '5':
                result += 5*pow(razrad,degree);
            break;
            case '6':
                result += 6*pow(razrad,degree);
            break;
            case '7':
                result += 7*pow(razrad,degree);
            break;
            case '8':
                result += 8*pow(razrad,degree);
            break;
            case '9':
                result += 9*pow(razrad,degree);
            break;
            case 'a':
                result += 10*pow(razrad,degree);
            break;
            case 'b':
                result += 11*pow(razrad,degree);
            break;
            case 'c':
                result += 12*pow(razrad,degree);
            break;
            case 'd':
                result += 13*pow(razrad,degree);
            break;
            case 'e':
                result += 14*pow(razrad,degree);
            break;
            case 'f':
                result += 15*pow(razrad,degree);
            break;
            default:

            break;
        }
        degree--;
    }
    return znak == 0 ? result : result * znak;
}

int main (int argc, char *argv[]){
    
    //argv[0] == комманде запуска программы
    if(argc < 3){
        cout << "Передано слишком мало параметров\n";
        return -1;
    }
    
    Registr *reg = new Registr();
    Memory *memory = new Memory();
    
    ifstream fin(argv[1], ifstream::in);

    //Проверка открытия файла
    if(!fin.is_open()){
        cout << "Файл не найден\n";
        return -1;
    }

    //Анализ файла с кодом
    bool comment = false;
    bool end_line = false;
    bool comand = false;
    int number_comand = -1;
    int number_operand = -1;
    bool read_number = false;
    int pole_count = 0;
    int instruction_counter = 0;

    fin.seekg(0, fin.beg);

    while(!fin.eof()){
        char *text = new char [N];
        fin >> text;
        if(comment == false){
            pole_count++;
        }
        for(int i = 0; text[i] != '\0'; i++){
            
            if(comment == true){
                comand = false;
                if(text[i] == ')'){
                    
                    comment = false;
                    pole_count = 0;

                    break;
                }
                continue;
            }
            else{
                if(text[i] == ';'){
                    comment = true;
                    comand = false;
                    break;   
                }
                comand = true;
            }
        }
        
        //Логика распознавания
        if(comand == true){
            switch(pole_count){
                case 1:
                    instruction_counter = str_to_int(text,10);
                break;
                case 2:
                    if(strcmp(text, "=") == 0){
                        number_comand = 0;
                    }
                    else if(strcmp(text, "READ") == 0){
                        number_comand = 10;
                    }
                    else if(strcmp(text, "WRITE") == 0){
                        number_comand = 11;
                    }
                    else if(strcmp(text, "LOAD") == 0){
                        number_comand = 20;
                    }
                    else if(strcmp(text, "STORE") == 0){
                        number_comand = 21;
                    }
                    else if(strcmp(text, "ADD") == 0){
                        number_comand = 30;
                    }
                    else if(strcmp(text, "SUB") == 0){
                        number_comand = 31;
                    }
                    else if(strcmp(text, "DEVIDE") == 0){
                        number_comand = 32;
                    }
                    else if(strcmp(text, "MUL") == 0){
                        number_comand = 33;
                    }
                    else if(strcmp(text, "JUMP") == 0){
                        number_comand = 40;
                    }
                    else if(strcmp(text, "JNEG") == 0){
                        number_comand = 41;
                    }
                    else if(strcmp(text, "JZ") == 0){
                        number_comand = 42;
                    }
                    else if(strcmp(text, "HALT") == 0){
                        number_comand = 43;
                    }
                    else if(strcmp(text, "NOT") == 0){
                        number_comand = 51;
                    }
                break;
                case 3:
                    
                    int value = 0;
                    int block = 0;
                    if(number_comand == 0){
                        block = str_to_int(text,16);
                    }
                    else{
                        block = str_to_int(text,10);
                    }

                    if(number_comand != 0){
                        //Если программируют просто команду
                        if(memory->commandEncode(number_comand,block, &value) == 0){
                            cout << "Слишком большой операнд! Число должно быть не больше 0x7F" << endl;
                            cout << "Строка: " << instruction_counter+1 << endl;
                            return 0;
                        }
                    }
                    else{
                        //Если программируют просто число
                        if(block > 0xffff){
                            cout << "Слишком большое число! Число должно быть не больше 0xFFFF" << endl;
                            cout << "Строка: " << instruction_counter << endl;
                            return 0;
                        }
                        else{
                            value = value | (0b1 << 14);
                            value = value | block;
                        }
                    }
                    //запись распознаной команды в файл памяти
                    memory->memorySet(instruction_counter,value,reg);
                    
                break;
            }
        }

        if(comment == false){
            if(pole_count == 3){
                end_line = true;
                pole_count = 0;
            }
        }
        
        if(end_line == true){
            
            end_line = false;
        }
    }
    if(memory->memorySave(argv[2]) == 0){
        cout << "Не удалось сохранить скомпилированный код";
    }
}