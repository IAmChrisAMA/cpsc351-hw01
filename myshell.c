#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// ========================= Early Iterations =================== //

#define BUFFSIZE 100

char buf[BUFFSIZE];
int  com_check = 0;

void execute(char**);
char** parse_args(char*, char*);
void output(char**);
bool exec_name(char*);

//void dir(int, char**);
void help();

// ============================== Main ========================== //

int main() {

    char** args;

    printf("              ______ _           _ _       \n");
    printf("             / _____) |         | | |      \n");
    printf(" ____  _   _( (____ | |__  _____| | |      \n");
    printf("|    \\| | | |\____  \\|  _ \\| ___ | | | \n");
    printf("| | | | |_| |_____) ) | | | ____| | |      \n");
    printf("|_|_|_|\\__  (______/|_| |_|_____)\\_)_)   \n");
    printf("      (____/                               \n");
    printf("                                           \n");
    printf("Type \'help\' for a list of commands.      \n");
    while(1) {

        printf("> ");
        
        fgets(buf, BUFFSIZE, stdin);
        args = parse_args(buf, " \n");

        execute(args);        
        free(args);

    }

}

// ============================ Functions ======================== //


void execute(char* args[]) {

    char* prog = args[0];

    if      (strcmp(prog, "help") == 0) { help();  }
    else if (strcmp(prog, "exit") == 0) { exit(0); }
    else if (exec_name(prog))           { com_check = 0; output(args); }
    else { 
        printf("%s: command not found\n", prog);
        ++com_check; 
        if(com_check >= 3) {printf("Need help? Type \'help\' for list of commands.\n\n"); }
    }

}

void output(char* args[]) {

    char* prog = args[0];

    int status;
    pid_t pid = fork();
    if (pid == 0) {

        execvp(prog, args);
        exit(0);

    } else { wait(&status); }

}

void help() {

    printf("myShell | v0.1\n");
    printf("These shell commands are defined. Type 'help' to see this list.\n");
    printf("     dir        help      vol     path\n" );
    printf("     tasklist   notepad   echo    color\n");
    printf("     ping\n"                              );

}

char** parse_args(char* buf, char* delim) {

	char** args = malloc(sizeof(char*));

	int len;
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

    if (strcmp(prog, "dir") == 0)      { return true; }
    if (strcmp(prog, "vol") == 0)      { return true; }
    if (strcmp(prog, "path") == 0)     { return true; }
    if (strcmp(prog, "tasklist") == 0) { return true; }
    if (strcmp(prog, "notepad") == 0)  { return true; }
    if (strcmp(prog, "echo") == 0)     { return true; }
    if (strcmp(prog, "color") == 0)    { return true; }
    if (strcmp(prog, "ping") == 0)     { return true; }
    return false;

}