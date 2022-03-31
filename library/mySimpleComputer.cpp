#include "mySimpleComputer.hpp"

void SimpleComputer::Start( void ){
    int action = -1;
    bool Exit = false; 
    int temp = 0, t_enter = 0;
    mainScreen->drawComputer();
    while(1){
        
        readKeys->readkey(&action);
        switch(action){
            case but_quit:
                Exit = true;
            break;
            case but_enter:
                readKeys->mytermregime(0,1,19,1,1);
                term->mt_gotoXY(26,1);
                temp = mainScreen->get_incstructionCounter();
                
                cout <<"Input: ";
                cin >> t_enter;
                
                memory->memorySet(temp,t_enter,registr);
                term->mt_gotoXY(26,1);
                for(int i = 1; i< 20; i++){
                    printf(" ");
                }
            break;
            case but_up:
                temp = mainScreen->get_incstructionCounter();
                if(temp > 9){
                    mainScreen->set_incstructionCounter( temp - 10 );
                }
            break;
            case but_down:
                temp = mainScreen->get_incstructionCounter();
                if(temp < 90 ){
                    mainScreen->set_incstructionCounter( temp + 10 );
                }
            break;
            case but_left:
                temp = mainScreen->get_incstructionCounter();
                if(temp > 0){
                    mainScreen->set_incstructionCounter( temp - 1 );
                }
            break;
            case but_right:
                temp = mainScreen->get_incstructionCounter();
                if(temp < 99){
                    mainScreen->set_incstructionCounter( temp + 1 );
                }
            break;
            case but_load:
                memory->memoryLoad("./memory_file/memory.dat");
            break;
            case but_save:
                memory->memorySave("./memory_file/memory.dat");
            break;
            case but_flags:
                readKeys->mytermregime(0,1,19,1,1);
                
                term->mt_gotoXY(26,1);
                cout <<"Input flags P: ";
                t_enter = 0;
                cin >> t_enter;
                registr->regSet(1,t_enter%2);

                term->mt_gotoXY(27,1);
                cout <<"Input flags 0: ";
                t_enter = 0;
                cin >> t_enter;
                registr->regSet(2,t_enter%2);
                
                term->mt_gotoXY(28,1);
                cout <<"Input flags M: ";
                t_enter = 0;
                cin >> t_enter;
                registr->regSet(3,t_enter%2);
                
                term->mt_gotoXY(29,1);
                cout <<"Input flags T: ";
                t_enter = 0;
                cin >> t_enter;
                registr->regSet(4,t_enter%2);
                
                term->mt_gotoXY(30,1);
                cout <<"Input flags E: ";
                t_enter = 0;
                cin >> t_enter;
                registr->regSet(5,t_enter%2);

                for(int i = 0; i < 5; i++){
                    term->mt_gotoXY(26+i,1);
                    for(int j = 0; j < 20;j++){
                        printf(" ");
                    }
                }
                
            break;
            case but_run:
                
            break;
            case but_step:
                
            break;
            case but_reset:
                
            break;
            case but_accumulator:
                
            break;
            case but_instructionCounter:
                
            break;
            
        }

        
        mainScreen->drawComputer();
        term->mt_gotoXY(26,1);
        sleep(0.05);
        if(Exit == true){
            break;
        }
    }
}

SimpleComputer::SimpleComputer(){
    fd = open("/dev/tty3",O_RDWR);

    registr = new Registr;
    term = new Term;
    memory = new Memory;
    readKeys = new ReadKey(fd);
    mainScreen = new ScreenDrawer(registr,term,memory);
    Start();
}
SimpleComputer::~SimpleComputer(){

    readKeys->mytermregime(1,0,0,1,1);
    term->mt_gotoXY(26,1);
    close(fd);

    delete registr;
    delete term;
    delete memory;
    delete readKeys;
    delete mainScreen;
}