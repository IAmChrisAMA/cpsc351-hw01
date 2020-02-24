/*
 ******************************
 *  Assignment #1 - myShell
 *  Chris Nutter, CPSC 351-04
 ******************************
 *
 *  myshell.c 
 *
 */ 

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// ========================== Declarations ====================== //

#define BUFFSIZE 1000                // max storage for arguments

char buf[BUFFSIZE];                 // storage for arguments
int  com_check = 0;                 // checks if you don't know how to work program

void execute(char**);               // executes given arguments

void output(char**);                // actual execution process
char** parse_args(char*, char*);    // parses the arguments to be readable

void help();                        // help function
bool exec_name(char*);              // function to check compatible commands

// ============================== Main ========================== //

int main() {

    char** args;

    printf("                      ______ _           _ _         \n");
    printf("                     / _____) |         | | |        \n");
    printf("         ____  _   _( (____ | |__  _____| | |        \n");
    printf("         |    \\| | | |\\____ \\|  _ \\| ___ | | |   \n");
    printf("         | | | | |_| |_____) ) | | | ____| | |       \n");
    printf("         |_|_|_|\\__  (______/|_| |_|_____)\\_)_)    \n");
    printf("               (____/                                \n\n");
    printf("                        v1.0 - GM                    \n");  
    printf("                     For Linux only.                 \n\n"); 
    printf("    notepad (vim), vol (df), path (pwd), color (tput)  \n");
    printf("    tasklist (top), dir (dir), echo (echo), help (help)\n\n");
    printf("Type \'help\' for a list of commands.      \n");
    while(1) {

        printf("> ");
        
        fgets(buf, BUFFSIZE, stdin);    // takes input from user
        args = parse_args(buf, " \n");  // parses input

        execute(args);                  // executes input
        free(args);                     // dealloc memory

    }

}

// ============================ Functions ======================== //


void execute(char* args[]) {

    char* prog = args[0];

    if      (strcmp(prog, "help") == 0) { help();  }                                            // checks if arg was "help"
    else if (strcmp(prog, "exit") == 0) { exit(0); }                                            // checks if arg was "exit"
    else if (exec_name(prog))           { com_check = 0; output(args); }                        // resets loop checker to 0 if you finally learned how to work the program... and then outputs
    else { 
        printf("%s: command not found\n", prog);                                                // failsafe for invalid commands
        ++com_check; 
        if(com_check >= 3) {printf("Need help? Type \'help\' for list of commands.\n\n"); }
    }     
        
}

void output(char* args[]) {

    char* prog = args[0];

    int status;
    pid_t pid = fork();         // child process
    if (pid == 0) {

        execvp(prog, args);     // execvp helps turn text into shell commands used by system
        exit(0);

    } else { wait(&status); }   // parent process

}

void help() {

    printf("myShell | v0.1\n");
    printf("These shell commands are defined. Type 'help' to see this list.\n");
    printf("     dir    help   df     pwd\n" );
    printf("     top    vim    echo   tput\n");
    printf("     ping\n"                    );

}

char** parse_args(char* buf, char* delim) {

	char** args = malloc(sizeof(char*));

	int len = 0;
	char* str;

	args[len] = NULL;
	str = strtok(buf, delim);

	while(str) {

		char** temp;

		args[len] = str;
		++len;

		temp = reallocarray(args, len + 1, sizeof(char*));  
        args = temp;
		
		args[len] = NULL;
		str = strtok(NULL, delim);

	}
    return args;
}

bool exec_name(char* prog) {

    if (strcmp(prog, "dir")      == 0) { return true; }
    if (strcmp(prog, "df")       == 0) { return true; }
    if (strcmp(prog, "pwd")      == 0) { return true; }
    if (strcmp(prog, "top") == 0) { return true; }
    if (strcmp(prog, "vim")  == 0) { return true; }
    if (strcmp(prog, "echo")     == 0) { return true; }
    if (strcmp(prog, "tput")    == 0) { return true; }
    if (strcmp(prog, "ping")     == 0) { return true; }
    return false;

}