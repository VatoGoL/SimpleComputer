#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <math.h>

#define N 100

using namespace std;

struct variables {
    //Адрес ячейки памяти
    int adress = 0;
    //Имя переменной
    char *name = new char [2];
    //Значение переменной
    int value = 0;
};/*
//функция преобразование числа в строковое число
char* int_to_str(int number, int razrad){

}*/
//функция преобразования строки в число
char* int_to_str(int value, int razrad){
    char *temp = new char [5];
    char *result = new char [5];
    int temp_value = value;
    int j = 0;
    for(int i = 0; i < 4; i++){
        if(temp_value == 0){
            break;
        }

        switch(temp_value % razrad){
            case 0:
                temp[i] = '0';
            break;
            case 1:
                temp[i] = '1';
            break;
            case 2:
                temp[i] = '2';
            break;
            case 3:
                temp[i] = '3';
            break;
            case 4:
                temp[i] = '4';
            break;
            case 5:
                temp[i] = '5';
            break;
            case 6:
                temp[i] = '6';
            break;
            case 7:
                temp[i] = '7';
            break;
            case 8:
                temp[i] = '8';
            break;
            case 9:
                temp[i] = '9';
            break;
            case 10:
                temp[i] = 'A';
            break;
            case 11:
                temp[i] = 'B';
            break;
            case 12:
                temp[i] = 'C';
            break;
            case 13:
                temp[i] = 'D';
            break;
            case 14:
                temp[i] = 'E';
            break;
            case 15:
                temp[i] = 'F';
            break;
            default:

            break;
        }
        temp_value /= razrad;
        j++;
    }
    
    for(int i = 0, l = 1; i < 4; i++){
        
        if(i < 4-j){
            result[i] = '0';
        }
        else{
            result[i] = temp[j-l];
            l++;
        }
    }
    
    delete[] temp;
    return result;
}

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
        if(str[i] >= '0' && str[i] <= '9' || str[i] >= 'A' && str[i] <= 'F'){
            degree++;
        }
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
            case 'A':
                result += 10*pow(razrad,degree);
            break;
            case 'B':
                result += 11*pow(razrad,degree);
            break;
            case 'C':
                result += 12*pow(razrad,degree);
            break;
            case 'D':
                result += 13*pow(razrad,degree);
            break;
            case 'E':
                result += 14*pow(razrad,degree);
            break;
            case 'F':
                result += 15*pow(razrad,degree);
            break;
            default:

            break;
        }
        degree--;
    }
    return znak == 0 ? result : result * znak;
}
int create_var(char *name,char *value, vector<int> *close_adress, vector<variables> *var, ofstream *fout){
    int adress_var = N;
    bool create;
            do
            {
                create = true;
                //Перебираем адреса
                if(adress_var > 0){
                    adress_var--;
                }
                else{
                    cout << "Ошибка: Переполнение памяти" << endl;
                    cout << "Невозможно создать переменную" << endl;
                    return -1;
                }

                for(int i = 0; i < close_adress->size(); i++){
                    if (adress_var == close_adress->at(i)){
                        create = false;
                    }
                }
                
            }while (!create);
            //Нашли адресс
            (*fout) << adress_var << " " << "=" << " " << "+" << value << endl;
            
            

            variables temp;
            temp.adress = adress_var;
            temp.name[0] = name[0];
            temp.value = 0;
            
            var->push_back(temp);
            close_adress->push_back(adress_var);
            return adress_var;
}
int my_input (char *text, vector<variables> *var, vector<int> *close_adress, int instruction_counter, ofstream *fout){
    if(text[0] >= 'A' && text[0] <= 'Z'){
        bool new_variable = true;
        int adress_var = N;

        for(int i = 0; i < var->size(); i++){
            //Если уже создавали такую переменную
            if(var->at(i).name[0] == text[0]){
                adress_var = i;
                new_variable = false;
                break;
            }
        }

        if(new_variable == false){
            (*fout) << instruction_counter << " " << "READ" << " " << var->at(adress_var).adress << endl;
        }
        else{
            adress_var = create_var(text,int_to_str(0,16),close_adress,var,fout);
            (*fout) << instruction_counter << " " << "READ" << " " << adress_var << endl;
        }
    }
    else{
        cout << " Ошибка: Название переменной задано некорректно!" << endl;
        cout << "Оно должно состоять из символов латинского алфавита находящихся в верхнем регистре" << endl;
        cout << "Строка: " << instruction_counter << endl;
        return -1;
    }
    return 0;
}
int my_print (const char *text, vector<variables> *var, int instruction_counter, ofstream *fout){
    if(text[0] >= 'A' && text[0] <= 'Z'){
        bool found_variable = false;
        int adress_var = N;
        char *var_name = new char[2];
        var_name[0] = text[0]; 

        for(int i = 0; i < var->size(); i++){
            //Ищем переменную
            if(var->at(i).name[0] == var_name[0]){
                adress_var = i;
                found_variable = true;
                break;
            }
        }
        delete[] var_name;
        if(found_variable == true){
            (*fout) << instruction_counter << " " << "WRITE" << " " << var->at(adress_var).adress << endl;
        }
        else{
            cout << "Ошибка: При выводе не была найдена переменная" << endl;
            cout << "Строка: " << instruction_counter << endl;
            return -1;
        }
        
    }
    else{
        cout << " Ошибка: Название переменной задано некорректно!" << endl;
        cout << "Оно должно состоять из символов латинского алфавита находящихся в верхнем регистре" << endl;
        return -1;
    }
    return 0;
}
int my_let (char *text, 
            vector<variables> *var, 
            vector<int> *close_adress, 
            int *instruction_counter, 
            ofstream *fout, 
            ifstream *fin){

    if(text[0] >= 'A' && text[0] <= 'Z'){
        bool new_variable = true;
        int adress_var = N;
        char *var_name = new char[2];
        var_name[0] = text[0]; 
        
        for(int i = 0; i < var->size(); i++){
            //Если уже создавали такую переменную
            
            if(var->at(i).name[0] == var_name[0]){
                adress_var = i;
                new_variable = false;
                break;
            }
        }
        
        delete[] var_name;
        //Создаём переменную если  её ещё нет
        if(new_variable == true){
            bool create;
            do
            {
                create = true;
                //Перебираем адреса
                if(adress_var > 0){
                    adress_var--;
                }
                else{
                    cout << "Ошибка: Переполнение памяти" << endl;
                    cout << "Невозможно создать переменную" << endl;
                    cout << "Строка: " << *instruction_counter << endl;
                    return -1;
                }

                for(int i = 0; i < close_adress->size(); i++){
                    if (adress_var == close_adress->at(i)){
                        create = false;
                    }
                }
                
            }while (!create);
            //Нашли адресс
            (*fout) << adress_var << " " << "=" << " " /*<< "+0000" << endl*/;
            

            variables temp;
            temp.adress = adress_var;
            temp.name[0] = text[0];
            temp.value = 0;
            //cout << temp.name << endl;
            var->push_back(temp);
            close_adress->push_back(adress_var);
        }

        //Обрабатываем присвоение, если оно есть
        if(text[1] != ';'){
            //Для обработки 2-х переменных
            char *first_variable_char = new char [2];
            first_variable_char[0] = '!';
            char *second_variable_char = new char [2];
            second_variable_char[0] = '!';
            char operation;
            //2 на случай если после равно 2 числа
            int first_variable_int = -1, second_variable_int = -1;

            //считали символ равно
            (*fin) >> text;
            //Считали 1 операнд
            (*fin) >> text;

            //Проверяем переменная ли это или просто константа
            //Переменная ? *;
            if(text[0] >= 'A' && text[0] <= 'Z'){
                //Переменная;
                first_variable_char[0] = text[0];
                if(text[1] == ';'){
                    //Логика
                    int temp_adress = -1;
                    for(int i = 0; i < var->size(); i++){
                        if(var->at(i).name[0] == first_variable_char[0]){
                            temp_adress = var->at(i).adress;
                            break;
                        }
                    }
                    if(temp_adress == -1){
                        cout << "Ошибка: Переменная не найдена" << endl;
                        cout << "Строка: " << *instruction_counter << endl;
                        return -1;
                    }

                    (*fout) << *instruction_counter << " " << "LOAD" << " " <<temp_adress << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                    (*fout) << *instruction_counter << " " << "STORE" << " " <<adress_var << endl;
                    close_adress->push_back(*instruction_counter);
                    
                    return 0;
                }
                //Считываем операцию
                (*fin) >> operation;

                //Считываем 2-й операнд
                (*fin) >> text;
                //Переменная ? Переменная
                if(text[0] >= 'A' && text[0] <= 'Z'){
                    //Переменная;
                    if(text[1] == ';'){
                        //Логика
                        second_variable_char[0] = text[0];

                        int temp_adress = -1;
                        for(int i = 0; i < var->size(); i++){
                            if(var->at(i).name[0] == first_variable_char[0]){
                                temp_adress = var->at(i).adress;
                                break;
                            }
                        }
                        if(temp_adress == -1){
                            cout << "Ошибка: Переменная не найдена" << endl;
                            cout << "Строка: " << instruction_counter << endl;
                            return -1;
                        }

                        (*fout) << *instruction_counter << " " << "LOAD" << " " << temp_adress << endl;
                        close_adress->push_back(*instruction_counter);
                        (*instruction_counter)++;
                        

                        //Вторая переменная
                        int temp_second_adress = -1;
                        for(int i = 0; i < var->size(); i++){
                            if(var->at(i).name[0] == second_variable_char[0]){
                                temp_second_adress = var->at(i).adress;
                                break;
                            }
                        }
                        if(temp_second_adress == -1){
                            cout << "Ошибка: Переменная не найдена" << endl;
                            cout << "Строка: " << instruction_counter << endl;
                            return -1;
                        }
                        
                        switch(operation){
                            case '+':
                                (*fout) << *instruction_counter << " " << "ADD" << " " << temp_second_adress << endl;
                            break;
                            case '-':
                                (*fout) << *instruction_counter << " " << "SUB" << " " << temp_second_adress << endl;
                            break;
                            case '/':
                                (*fout) << *instruction_counter << " " << "DIVIDE" << " " << temp_second_adress << endl;
                            break;
                            case '*':
                                (*fout) << *instruction_counter << " " << "MUL" << " " << temp_second_adress << endl;
                            break;
                        }
                        close_adress->push_back(*instruction_counter);
                        (*instruction_counter)++;
                        (*fout) << *instruction_counter << " " << "STORE" << " " << temp_adress << endl;
                        close_adress->push_back(*instruction_counter);
                        (*instruction_counter)++;
                        
                        delete[] first_variable_char;
                        delete[] second_variable_char;

                        return 0;
                    }

                    
                }
             
            }
            else{
                int temp_value = str_to_int(text,10);
                if(temp_value > 0x7f){
                    cout << "Ошибка: Присваивается слишком большое значение переменной" << endl;
                    cout << "Строка: " << instruction_counter;
                    return -1;
                }
                char *str;
                str = int_to_str(temp_value,16);
                (*fout) <<"+"<< str << endl;
                delete[] str;
            }
        }
        else{
            (*fout) << "+0000" << endl;
        }
    }
    else{
        cout << "Ошибка: Название переменной задано некорректно!" << endl;
        cout << "Оно должно состоять из символов латинского алфавита находящихся в верхнем регистре" << endl;
        cout << "Строка: " << instruction_counter << endl;
        return -1;
    }
    return 0;
}
int my_goto (char *text, vector<int> *close_adress, ofstream *fout, ifstream *fin, int *instruction_counter){
    //Обрезаем ;
    char *temp_text = new char [100];
    for(int i = 0; text[i] != ';' && text[i] != '\0'; i++){
        temp_text[i] = text[i];
    } 
    
    int t = str_to_int(temp_text,10);
    
    if(t > 99 || t < 0){
        cout << "Ошибка: Ссылка ведет за границы памяти" << endl;
        cout << "Строка: " << *instruction_counter << endl;
        return -1;
    }

    //Проверяем можем ли мы гарантировать, что этот адрес ведет на команду
    bool search = false;
    if(t < *instruction_counter){
        search = true;
    }
    else if( t == *instruction_counter){
        cout << "Ошибка: Обнаружено бесконечное зацикливание, ссылка ведет на саму себя" << endl; 
        cout << "Строка: " << *instruction_counter << endl;
        return -1;
    }
    if(search == false){
        cout << "Предупреждение: Ссылка ведет на неизвестный адрес" << endl;
        cout << "Строка: " << *instruction_counter << endl;
    }

    (*fout) << *instruction_counter << " " << "JUMP" << " " << t << endl;  
    return 0;
}

int my_if(char *text, vector<variables> *var, vector<int> *close_adress, ofstream *fout, ifstream *fin, int *instruction_counter, char *arg_2){
    
    char *first_variable_char = new char [2];
    first_variable_char[0] = '!';
    char *second_variable_char = new char [2];
    second_variable_char[0] = '!';
    char operation;
    //2 на случай если после равно 2 числа
    int first_variable_pos = -1, second_variable_pos = -1;
    int first_var = -1, second_var = -1;
    int goto_pos = -1;
    
    //считываем первый операнд
    if(text[0] >= 'A' || text[0] <= 'Z'){
        first_variable_char[0] = text[0];
        
    }
    
    //считывание операции
    (*fin) >> operation;
    
    //считываем второй операнд
    (*fin) >> text;
    if(text[0] >= 'A' || text[0] <= 'Z'){
        second_variable_char[0] = text[0];
        
    }


    if(first_variable_char[0] != '!'){
        if(second_variable_char[0] != '!'){

            for(int i = 0; i < var->size(); i++){
                if(var->at(i).name[0] == first_variable_char[0]){
                    first_variable_pos = var->at(i).adress;
                }
                if(var->at(i).name[0] == second_variable_char[0]){
                    second_variable_pos = var->at(i).adress;
                }
            }

            if(first_variable_pos == -1){
                cout << "Ошибка: 1 переменная из условия не объявлена" << endl;
                cout << "Строка: " << *instruction_counter << endl;
                return -1;
            }
            if(second_variable_pos == -1){
                cout << "Ошибка: 2 переменная из условия не объявлена" << endl;
                cout << "Строка: " << *instruction_counter << endl;
                return -1;
            }

            //GOTO
            (*fin) >> text;
            //cout << text;
            //Адрес
            (*fin) >> text;
            //cout << text;
            char *t_text = new char [N];
            for(int i = 0; text[i] != ';' && text[i] != '\0'; i++){
                t_text[i] = text[i];
            }
            goto_pos = str_to_int(t_text, 10);
            if(goto_pos < 0 || goto_pos > 99){
                cout << "Ошибка: Вышли за груницы массива" << endl;
                cout << "Строка: " << *instruction_counter << endl;
                return -1;
            }
            if(goto_pos > *instruction_counter){
                cout << "Предупреждение: Ссылка ведет на неизвестный адрес" << endl;
                cout << "Строка: " << *instruction_counter << endl;
            }
            switch(operation){
                case '>':
                    (*fout) << *instruction_counter << " " << "LOAD" << " " << second_variable_pos << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                    (*fout) << *instruction_counter << " " << "SUB" << " " << first_variable_pos << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                    (*fout) << *instruction_counter << " " << "JNEG" << " " << t_text << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                break;
                case '<':
                    (*fout) << *instruction_counter << " " << "LOAD" << " " << first_variable_pos << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                    (*fout) << *instruction_counter << " " << "SUB" << " " << second_variable_pos << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                    (*fout) << *instruction_counter << " " << "JNEG" << " " << t_text << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                break;
                case '=':
                    (*fout) << *instruction_counter << " " << "LOAD" << " " << first_variable_pos << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                    (*fout) << *instruction_counter << " " << "SUB" << " " << second_variable_pos << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                    (*fout) << *instruction_counter << " " << "JZ" << " " << t_text << endl;
                    close_adress->push_back(*instruction_counter);
                    (*instruction_counter)++;
                break;
            }
        }
        //перем и цифра
        else{
            cout << "Ошибка: Нет возможности вставить в условие константу" << endl;
            return -1;
        }
    }
    else{
        cout << "Ошибка: Нет возможности вставить в условие константу" << endl;
        return -1;
    }
}

int main (int argc, char *argv[]){
    
    //argv[0] == комманде запуска программы
    if(argc < 3){
        cout << "Передано слишком мало параметров\n";
        return -1;
    }
    
    
    ifstream fin(argv[1], ifstream::in);
    ofstream fout(argv[2], ofstream::trunc);

    //Проверка открытия файла
    if(!fin.is_open()){
        cout << "Файл не найден\n";
        return -1;
    }
    

    //Анализ файла с кодом
    bool comment = false;
    bool found_adress = true;
    bool end_line = false;
    bool comand = false;
    bool exit = false;
    int number_comand = -1;
    int temp;
    bool read_number = false;
    int pole_count = 0;
    int instruction_counter = 0;
    vector<variables> var;
    vector<int> close_adress;

    fin.seekg(0, fin.beg);
    //create_var("Y", int_to_str(0,16),&close_adress,&var,&fout);
    //create_var("Z", int_to_str(0,16),&close_adress,&var,&fout);
    while(!fin.eof()){
        char *text = new char [N];
        fin >> text;
        
        pole_count++;
        
        switch(pole_count){
            case 1:
                //instruction_counter++;
            break;
            case 2:
                if(strcmp(text,"REM") == 0){
                    comment = true;
                    //Пролистываем коментарий до завершающего конца строки
                    while(comment == true && !fin.eof()){
                        fin >> text;
                        for(int i = 0; text[i] != '\0'; i++){
                            //Возможно ошибка и надо вернуть ;
                            if(text[i] == ';'){
                                //cout << "НАШЁЛ СИМВОЛ ПЕРЕНОСА СТРОКИ!";
                                comment = false;
                                break;
                            }
                        }    
                    }
                    pole_count = 0;
                }
                else if(strcmp(text,"INPUT") == 0){
                    number_comand = 10;
                }
                else if(strcmp(text,"PRINT") == 0){
                    number_comand = 11;
                }
                else if(strcmp(text,"LET") == 0){
                    number_comand = 12;
                }
                else if(strcmp(text,"IF") == 0){
                    number_comand = 20;
                }
                else if(strcmp(text,"GOTO") == 0){
                    number_comand = 21;
                }
                else if(strcmp(text,"END;") == 0){
                    //Конец программы
                    temp = instruction_counter;
                    do{
                        found_adress = true;
                        for(int i = 0; i < close_adress.size(); i++){
                            if(instruction_counter == close_adress.at(i)){
                                found_adress = false;
                                instruction_counter++;
                                break;
                            }
                        }
                        if(instruction_counter == N){
                            cout << "Ошибка: Переполнение памяти" << endl;
                            cout << "Не нашлось место для команды" << endl;
                            cout << "Строка: " << temp << endl;
                        }
                    }while(!found_adress);

                    fout << instruction_counter << " " << "HALT" << " " << "00" << endl;
                    return 0;
                }
                
            break;
            case 3:
                temp = instruction_counter;
                do{
                    found_adress = true;
                    for(int i = 0; i < close_adress.size(); i++){
                        if(instruction_counter == close_adress.at(i)){
                            found_adress = false;
                            instruction_counter++;
                            break;
                        }
                    }
                    if(instruction_counter == N){
                        cout << "Ошибка: Переполнение памяти" << endl;
                        cout << "Не нашлось место для команды" << endl;
                        cout << "Строка: " << temp << endl;
                    }
                }while(!found_adress);
                

                switch(number_comand){
                    //INPUT
                    case 10:
                        my_input(text,&var,&close_adress,instruction_counter,&fout);
                        close_adress.push_back(instruction_counter);
                        instruction_counter++;
                    break;
                    //PRINT
                    case 11:
                        my_print(text,&var,instruction_counter,&fout);
                        close_adress.push_back(instruction_counter);
                        instruction_counter++;
                    break;
                    //LET
                    case 12:
                        my_let(text,&var,&close_adress,&instruction_counter,&fout,&fin);
                        
                    break;
                    //IF
                    case 20:
                        my_if(text,&var,&close_adress,&fout,&fin,&instruction_counter,argv[2]);
                    break;
                    //GOTO
                    case 21:
                        my_goto(text,&close_adress,&fout,&fin,&instruction_counter);
                        close_adress.push_back(instruction_counter);
                        instruction_counter++;
                    break;
                }
                //instruction_counter++;
            break;
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
    
}