#define _GNU_SOURCE
#define READLINE_LIBRARY
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>

extern void rl_replace_line(const char *text, int clear_undo);

int main()
{
    while (1)
    {
        char *input = readline("shell> ");
        if (!strcmp(input, "hclear"))
            clear_history();
        if (input && *input)
        {
            printf("HERE  \n");
            add_history(input);
        }

        // Replace the input line in the readline buffer
        rl_replace_line("new line", 0);
        rl_redisplay();  // Needed to update the displayed input line
    }
}
