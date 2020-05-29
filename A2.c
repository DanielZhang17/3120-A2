/* File:     A2.c
 * Author:   Anran Zhang   B00747547
 * Date:     2020/05/25
 * Version:  1.1
 *
 * Purpose:  This program is a simple C shell.
 * Notes:    I made the assumption that the max length of one line is 80
 *           and max number of tokens on one line is 20.
 *           Ideally i would dynamically adjust this.
 *           Command used to compile: gcc A2.c -o A2.out
 */
#include <stdio.h>
#include <string.h>
#include <wait.h>
#include <zconf.h>
#include <stdlib.h>

//define some constants
#define MAX_LENGTH 80 //assuming the max length of a line is 80 characters
#define MAX_TOKEN 20 //assuming the max number of tokens on one line is 20
#define DELIM " \t\r\n\a"

//function declaration
char **split_input(char * input);//splits input into tokens
int isPipe(char **arg);//checks if input is pipe and returns a index if it is
int isMulti(char **arg);//checks if multiple commands are in the input
void handleMulti(char **arg);//processes multiple commands on one line
void handlePipe(char **command1, char **command2);//handle pipes
int runCommand(char **cmd);//runs one single command used in handleMulti
//global variables
int status;//stores the status of the child program
int arguments;//stores the number of tokens in the input
//used to store commands separated by pipe
char **cmd1;
char **cmd2;

int main()
{
    int quit = 1;
    size_t line_buf_size = MAX_LENGTH;
    while (quit)
    {
        char *input = malloc(MAX_LENGTH * sizeof(char));//stores user input
        //initialize them here
        cmd1 = malloc(MAX_TOKEN * sizeof(char *));
        cmd2 = malloc(MAX_TOKEN * sizeof(char *));
        printf("$ ");
        getline(&input,&line_buf_size,stdin);//reads one line from stdin
        //handles empty input, so that it does not cause segmentation fault
        if (strcmp(input,"\n")==0)
            continue;
        char **arg = split_input(input);
        //if the command is 'exit', exit the shell
        if (strcmp(arg[0], "exit")==0)
            quit = 0;
        else
        {
            //create a new process with fork()
            pid_t pid;
            pid = fork();
            int index = isPipe(arg);
            if (pid < 0) {
                fprintf(stderr, "Unable to create process with fork()\n");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0) //child successfully created
            {
                if (index!=0)//pipe is used,handle it
                {
                    int c =0; //counter for cmd2
                    //puts the command after '|' into cmd2
                    for (int i = index+1; i < arguments; i++) {
                        cmd2[c] = arg[i];
                        printf("%s ",cmd2[c]);
                        c++;
                    }
                    handlePipe(cmd1,cmd2);
                }
                else
                    execvp(arg[0],arg);
                //print error msg if gets here
                printf( "Something went wrong\n");
            }
            else
            {
                //parent process waits for the child to finish
                waitpid(pid,&status,WUNTRACED);
            }
        }
        //release memory
        free(input);
        free(arg);
        free(cmd1);
        free(cmd2);
        //reset global variables
        arguments = 0;
        //“reap” any background jobs which have terminated
        int pid = waitpid(-1,NULL,WNOHANG);
        if (pid!=-1)
            printf("Process %d terminated\n",pid);
    }
    return EXIT_SUCCESS;
}

//splits the input into tokens
char **split_input(char * input)
{
    //printf("Input: %s",input);
    char ** arg = malloc(MAX_TOKEN * sizeof(char *)); //store tokens
    char * token = strtok(input,DELIM);
    int c = 0; // counts the number of arguments
    while (token != NULL)
    {
        arg[c] = token;
        token = strtok(NULL,DELIM);
        c++;
    }
    arguments = c;
    return arg;
}
//checks if input is a pipe and returns the index of '|' token
int isPipe(char **arg)
{
    for (int i = 0; i < arguments; ++i) {
        if (strcmp(arg[i],"|")==0)
            return i;
        //copy the content to cmd1
        cmd1[i] = arg[i];
    }
    return 0;
}
//checks if multiple commands are on one line
int isMulti(char **arg)
{
    for (int i = 0; i < arguments; ++i) {
        if (strcmp(arg[i],";")==0)
            return 0;
    }
    return 1;
}
//handles multiple commands on one line
void handleMulti(char **arg)
{
    char **temp = malloc(MAX_TOKEN * sizeof(char *));
    int c =0;
    for (int i = 0; i < arguments; ++i)
    {
        temp[i] = arg[i];
        if (arg[i])
    }
    free(temp);//release memory
}
//this handles pipes
//I tried to do this in main() but it is getting too messy
void handlePipe(char **command1, char **command2)
{
    int fd[2];
    pid_t child_pid;
    if (pipe(fd) != 0)
        fprintf(stderr,"failed to create pipe");

    if ((child_pid = fork()) == -1)
        fprintf(stderr,"fork() failed");

    if (child_pid == 0)
    {
        //child process executes cmd1
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execvp(command1[0], command1);
    }
    else
    {
        //parent process executes cmd2 after child returns the data
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execvp(command2[0], command2);
    }
}
//executes the command cmd
int runCommand(char **cmd)
{

    return 0;
}