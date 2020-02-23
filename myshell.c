#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFSIZE 1000


char buf[BUFFSIZE];
int  com_check = 0;

void execute(char**);
char** parse_args(char*, char*);

void dir(int, char**);
void help();


int main() {

    char** args;

    printf("Welcome to MyShell\n");
    printf("Please enter a command\n");

    while(1) {

        printf("~> ");
        //char input;
        fgets(buf, BUFFSIZE, stdin);
        args = parse_args(buf, " \n");

        execute(args);        
        //free(args);

    }

}

void execute(char** args) {

    pid_t pid = fork();
    char* prog = args[0];

    if      (strcmp(prog, "help") == 0)             { help(); }
    else if (pid == 0 && strcmp(prog, "exit") == 0) { exit(0); }
    else if (pid == 0 && strcmp(prog, "dir")  == 0) { dir(prog, args); }
    else { 
        printf("%s: command not found\n", prog);
        ++com_check; 
        if(com_check >= 3) {printf("Need help? Type \'help\' for list of commands.\n"); }
    }

}


void help() {

    printf("myShell help output, version v0.1\n");
    printf("These shell commands are defined. Type 'help' to see this list.\n");
    printf("dir       help      vol     path\n");
    printf("tasklist  notepad   echo    color\n");
    printf("ping\n");

}

void dir(int argc, char* argv[]) {

    if(argc == 0) { execvp(argv[0], argv); }
    else          { /*TODO*/ return; }

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
}