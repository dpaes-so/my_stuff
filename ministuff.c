#define _GNU_SOURCE
#define READLINE_LIBRARY

#include <stdio.h>  // Include this before readline
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

extern void rl_replace_line(const char *text, int clear_undo);

int main()
{
    while (1)
    {
        char *input = readline("shell> ");
        if (!input)  
            break;

        if (!strcmp(input, "hclear"))
            clear_history();
        if(!strcmp(input,"cd"))
        {
            rl_replace_line("not yet xD", 0); //not working idk im angy >:(
            rl_redisplay();
        }
        if(!strcmp(input,"$HOME"))
            printf("Home directory: %s\n", getenv("HOME"));
        if (*input)
        {
            printf("HERE  \n");
            add_history(input);
        }
        printf("INPUT = %s\n",input);
        free(input);
    }

    return 0;
}
