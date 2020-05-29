/* File:     A2.c
 * Author:   Anran Zhang   B00747547
 * Date:     2020/05/25
 * Version:  1.0
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
char **split_input(char * input);

int main()
{
    int quit = 1;
    int status;
    size_t line_buf_size = MAX_LENGTH;
    while (quit)
    {
        char *input = malloc(MAX_LENGTH * sizeof(char));//stores user input
        printf("$ ");
        getline(&input,&line_buf_size,stdin);//reads one line from stdin
        //handles empty input, so that it does not cause segmentation fault
        if (strcmp(input,"\n")==0|strcmp(input,"\n")==0)
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
            if (pid < 0) {
                fprintf(stderr, "Unable to create process with fork()\n");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0) //child successfully created
            {

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
    return arg;
}