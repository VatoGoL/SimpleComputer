#include "readKey.hpp"

ReadKey::ReadKey(int Fd){
    settings_Term = new termios;
    def_Settings = new termios;
    fd = Fd;
    tcgetattr (fd, def_Settings);
}

int ReadKey::recognize (char *command){
    
    if(strcmp(command,"\E[A")  == 0){
        return but_up;
    }
    else if(strcmp(command,"\E[B") == 0){
        return but_down;
    }
    else if(strcmp(command,"\E[C") == 0){
        return but_right;
    }
    else if(strcmp(command,"\E[D") == 0){
        return but_left;
    }
    else if(strcmp(command,"l") == 0){
        return but_load;
    }
    else if(strcmp(command,"s") == 0){
        return but_save;
    }
    else if(strcmp(command,"r") == 0){
        return but_run;
    }
    else if(strcmp(command,"t") == 0){
        return but_step;
    }
    else if(strcmp(command,"i") == 0){
        return but_reset;
    }
    else if(strcmp(command,"q") == 0){
        return but_quit;
    }
    else if(strcmp(command,"\E[[E") == 0){
        return but_accumulator;
    }
    else if(strcmp(command,"\E[17~") == 0){
        return but_instructionCounter;
    }
    else if(strcmp(command,"\E[[D") == 0){
        return but_enter;
    }
    else if(strcmp(command,"f") == 0){
        return but_flags;
    }
    else{
        return -1;
    }
}
    
int ReadKey::readkey (int *key){
    char *command = new char [size_Command];

    mytermregime(0,0,0,0,1);
    read(fd,command,size_Command);
    
    *key = recognize(command);

    delete[] command;
    return 0;
}
int ReadKey::mytermsave (void){
    
    FILE *file_save = fopen("./memory_file/terminalSettings.dat","wb");
    if(file_save == NULL){
        printf("Ошибка открытия файла сохранения настроек терминала");
        return -1;
    }

    tcgetattr (fd, settings_Term);
    
    fwrite(&settings_Term->c_iflag,sizeof(settings_Term->c_iflag), 1, file_save);
    fwrite(&settings_Term->c_oflag,sizeof(settings_Term->c_oflag), 1, file_save);
    fwrite(&settings_Term->c_lflag,sizeof(settings_Term->c_lflag), 1, file_save);
    fwrite(&settings_Term->c_cflag,sizeof(settings_Term->c_cflag), 1, file_save);
    fwrite(&settings_Term->c_cc,sizeof(settings_Term->c_cc[0]), NCCS, file_save);

    fclose(file_save);
}
int ReadKey::mytermrestore (void){
    
    FILE *file_read = fopen("./memory_file/terminalSettings.dat", "rb");
    if(file_read == NULL){
        printf("Ошибка открытия файла сохранения настроек терминала");
        return -1;
    }
    fread(&settings_Term->c_iflag,sizeof(settings_Term->c_iflag),1,file_read);
    fread(&settings_Term->c_oflag,sizeof(settings_Term->c_oflag),1,file_read);
    fread(&settings_Term->c_lflag,sizeof(settings_Term->c_lflag),1,file_read);
    fread(&settings_Term->c_cflag,sizeof(settings_Term->c_cflag),1,file_read);
    fread(&settings_Term->c_cc,sizeof(settings_Term->c_cc[0]),NCCS,file_read);

    tcsetattr (fd, TCSADRAIN, settings_Term);

    fclose(file_read);
}
int ReadKey::mytermregime (int regime, int vtime, int vmin, int echo, int sigint = 1){
    
    if(regime){
        settings_Term->c_lflag |= ICANON;
    }
    else{
        settings_Term->c_lflag &= ~ICANON;
    }

    if(echo){
        settings_Term->c_lflag |= ECHO;
    }
    else{
        settings_Term->c_lflag &= ~ECHO;
    }

    if(sigint){
        settings_Term->c_lflag |= ISIG;
        settings_Term->c_cc[VQUIT] = VQUIT;
    }
    else{
        settings_Term->c_lflag &= ~ISIG;
    }
    
    if(!regime){
        settings_Term->c_cc[VTIME] = vtime;
        settings_Term->c_cc[VMIN] = vmin;
    }

    tcsetattr (fd, TCSADRAIN, settings_Term);
    return 0;
}
termios* ReadKey::get_deflautSettings(void){
    return def_Settings;
}

ReadKey::~ReadKey(){
    delete def_Settings;
    delete settings_Term;
}