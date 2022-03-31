#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

enum keys {
    but_up = 0, 
    but_down, 
    but_left, 
    but_right, 
    but_load, 
    but_save, 
    but_run, 
    but_step, 
    but_reset, 
    but_accumulator, 
    but_instructionCounter, 
    but_enter, 
    but_quit,
    but_flags
};

class ReadKey {
private:
    int fd;
    static const int size_Command = 11;
    termios *settings_Term;
    termios *def_Settings;
    
public:
    ReadKey(int Fd);
    int recognize (char *command);
    int readkey (int *key);
    int mytermsave (void);
    int mytermrestore (void);
    int mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
    termios *get_deflautSettings(void);
    virtual ~ReadKey();
};