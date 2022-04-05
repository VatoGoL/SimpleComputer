#include "mySimpleComputer.hpp"

void SimpleComputer::Start( void ){
    int action = -1;
    bool Exit = false; 
    bool runTimer = false;
    int temp = 0, t_enter = 0;
    mainScreen->drawComputer();
    startTimer();
    signal(SIGALRM, signalTimer);
    signal(SIGUSR1, signalUsr);

    while(1){
        registr->regGet(4,&ignore_imp);
        readKeys->readkey(&action);

        if(signlTimer == true){

            if(!ignore_imp){
                int t = mainScreen->get_incstructionCounter();
                t += 1;
                if(t < 100){
                    mainScreen->set_incstructionCounter(t);
                }
                else{
                    raise(SIGUSR1);
                }
            }
            signlTimer = false;
        }
        if(signlUsr == true){
            if(!ignore_imp){
                mainScreen->set_incstructionCounter(0);
                action = but_run;
            }
            
            signlTimer = false;
            signlUsr = false;
        }

        switch(action){
            case but_quit:
                Exit = true;
            break;
            case but_enter:
                if(ignore_imp){
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
                }
                
            break;
            case but_up:
                if(ignore_imp){
                    temp = mainScreen->get_incstructionCounter();
                    if(temp > 9){
                        mainScreen->set_incstructionCounter( temp - 10 );
                    }
                }
                
            break;
            case but_down:
                if(ignore_imp){
                    temp = mainScreen->get_incstructionCounter();
                    if(temp < 90 ){
                        mainScreen->set_incstructionCounter( temp + 10 );
                    }
                }
            break;
            case but_left:
                if(ignore_imp){
                    temp = mainScreen->get_incstructionCounter();
                    if(temp > 0){
                        mainScreen->set_incstructionCounter( temp - 1 );
                    }
                }
            break;
            case but_right:
                if(ignore_imp){
                    temp = mainScreen->get_incstructionCounter();
                    if(temp < 99){
                        mainScreen->set_incstructionCounter( temp + 1 );
                    }
                }
            break;
            case but_load:
                if(ignore_imp){
                    memory->memoryLoad("./memory_file/memory.dat");
                }
                
            break;
            case but_save:
                if(ignore_imp)
                memory->memorySave("./memory_file/memory.dat");
                
            break;
            case but_flags:
                if(ignore_imp){
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
                        for(int j = 0; j < 30;j++){
                            printf(" ");
                        }
                    }
                }
            break;
            case but_run:
                if(ignore_imp){
                    registr->regSet(4,0);
                }
                else{
                    registr->regSet(4,1);
                }
            break;
            case but_step:
                
            break;
            case but_reset:
                if(ignore_imp){
                    registr->regInit();
                    memory->memoryInit();
                    mainScreen->set_incstructionCounter(0);
                    mainScreen->set_accumulator(0);
                }
            break;
            case but_accumulator:
                if(ignore_imp){
                    readKeys->mytermregime(0,1,19,1,1);

                    term->mt_gotoXY(26,1);

                    cout << "Input Accumulator: ";
                    cin >> t_enter;

                    mainScreen->set_accumulator(t_enter);
                    term->mt_gotoXY(26,1);
                    for(int j = 0; j < 30;j++){
                        printf(" ");
                    }
                }
            break;
            case but_instructionCounter:
                if(ignore_imp){
                    readKeys->mytermregime(0,1,19,1,1);

                    term->mt_gotoXY(26,1);

                    cout << "Input Instruction Counter: ";
                    cin >> t_enter;

                    mainScreen->set_incstructionCounter(t_enter);
                    term->mt_gotoXY(26,1);
                    for(int j = 0; j < 30;j++){
                        printf(" ");
                    }
                }
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

void SimpleComputer::startTimer( void ){
    nval.it_interval.tv_sec = 0;
    nval.it_interval.tv_usec = 300000; //0,3 sec
    nval.it_value.tv_sec = 0;
    nval.it_value.tv_usec = 300000; //0.3 sec

    setitimer(ITIMER_REAL,&nval,&oval);
}

bool SimpleComputer::signlTimer = false;
bool SimpleComputer::signlUsr = false;

void SimpleComputer::set_signlTimer( bool value ){
    SimpleComputer::signlTimer = value;
}
void SimpleComputer::set_signlUsr( bool value ){
    SimpleComputer::signlUsr = value;
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

void signalTimer (int signo){
    SimpleComputer::set_signlTimer(true);
}
void signalUsr (int signo){
    SimpleComputer::set_signlUsr(true);
}