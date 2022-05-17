#include "scMemory.hpp"


int Memory::memoryInit(){
    for(int i = 0; i < memory_size; i++){
        memory[i] = 0;
    }
    return 1;
}

int Memory::memorySet(int adress, int value, Registr *reg){
    //Проверка на выход за размер памяти
    if(adress < 0 || adress > memory_size-1){
        //Флаг с ошибкой
        reg->regSet(3,1);
        return -1;
    }
    if(value > 0xFFFF){
        return -1;
    }
    //Если не вышли за неё
    memory[adress] = value;
    return 0;
}
int Memory::memoryGet(int adress, int *value, Registr *reg){
    //Проверка на выход за размер памяти
    if(adress < 0 || adress > memory_size-1){
        //Флаг с ошибкой
        reg->regSet(3,1);
        return -1;
    }
    //Если не вышли за неё
    *value = memory[adress];
    return 0;
}

int Memory::memorySave(char *filename){
    //удалим прошлое сохранение
    remove(filename);

    FILE *memory_file = NULL;
    memory_file = fopen(filename, "wb");

    if(memory_file == NULL){
        return 0;
    }
    //сохраняем данные с "оперативной памяти"
    fwrite(memory,sizeof(int),memory_size,memory_file);
    fclose(memory_file);    
    return 1;
}

int Memory::memoryLoad(char *filename){
    FILE *memory_file = NULL;
    memory_file = fopen(filename, "rb");

    if(memory_file == NULL){
        return -1;
    }
    //считываем данные в "оперативную память"
    fread(memory,sizeof(int),memory_size,memory_file);
    fclose(memory_file);    
    return 1;
}

int Memory::commandEncode(int command, int operand, int *value){
    //проверка на диапазон допустимых значений операнда
    if(operand < 0 ||operand > MAX_COMMAND_ODERAND-1){
        return 0;
    }
    //Проверка на знание кодируемой комманды
    bool succeful_command = false;
    for(int i = 0; i < command_size; i++){
        if(command == command_list[i]){
            succeful_command = true;
        }
    }
    if(succeful_command == false){
        return 0;
    }


    //Кодирование
    int command_temt = 0b0; //шаблон кодируемой комманды
    //Кодирование операнда
    command_temt = command_temt | operand;
    //Кодирование комманды
    command_temt = command_temt | (command << 7); //сдвигаем на 7 бит чтобы не задеть операнд
    //помещаем закодированную коммманду с операндом в value
    *value = command_temt;
    return 1;
}

int Memory::commandDecode(int value, int *command, int *operand, Registr *reg){
     //Создаём временные переменные для комманды и операнда
    int command_temp = 0b0, operand_temp = 0b0;
    //Проверка на то что это вообще комманда
    
   
    //int command_temp = 0b0, operand_temp = 0b0;
    //Считываем операнд
    operand_temp = operand_temp | value;
    //Обрезаем лишнюю часть
    operand_temp = operand_temp % MAX_COMMAND_ODERAND;

    //Считываем комманду
    command_temp = command_temp | (value >> 7); //Сдвигаем вправо тчобы обрезать операнд

    //Проверка на знание декодируемой комманды
    bool succeful_command = false;
    for(int i = 0; i < command_size; i++){
        if(command_temp == command_list[i]){
            succeful_command = true;
        }
    }
    if(succeful_command == false){
        reg->regSet(5,1); //Указана неверная комманда
        return -1;
    }

    //Записываем результат декодирования
    *operand = operand_temp;
    *command = command_temp;
    return 0;
}

int Memory::memoryShow(){
    printf("\nMemory: ");
    for(int i = 0; i < memory_size; i++){
        printf("%d ", memory[i]);
    }
    printf("\n");
}

Memory::Memory(){
    memoryInit();
}
Memory::~Memory(){
};