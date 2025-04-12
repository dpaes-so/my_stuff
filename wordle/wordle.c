#include "wordle.h"
int get_word(char *wlist,char ***words)
{
    int fd;
    int i;
    char *str;
    i = 0;
    fd = open(wlist,O_RDONLY);
    if(fd < 0)
    {
        ft_printf("FAILED TO OPEN THE WORD LIST\n");
        exit(1);
    }
    *words = ft_calloc(sizeof(char *), MAX_WORDS);
    while(1)
    {
        str = get_next_line(fd);
        if(!str)
            break;
        if(ft_strlen(str) == 6)
        {
            (*words)[i] = str;
            // ft_printf("str = %s",(*words)[i]);
            i++;
        }
        else
            free(str);
    }
    (*words)[i] = NULL;
    close(fd);
    printf("\n\n\n");
    return(i);
}

void print_feedback(char *guess, char *word)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(word);
    while(i < len - 1)
    {
        if(guess[i] == word[i])
            printf(GREEN "%c" RESET, guess[i]);
        else if(ft_strchr(word,guess[i]))
            printf(YELLOW "%c" RESET, guess[i]);
        else
            printf(RED "%c" RESET, guess[i]);
        i++;
    }
    printf("\n");
}

int main()
{
    char **words;
    char *word;
    int guesses = 0;
    int attempts = 6;//HOW MANY ATTEMPS MAX TO GUESS THE WORD
    char **guess = ft_calloc(attempts,sizeof(char *));
    int word_count = get_word("words.txt",&words);
    srand(time(NULL));
    word = words[rand() % word_count];
    printf(YELLOW " __          ________ _      _____ ____  __  __ ______   _______ ____  \n");
    printf(" \\ \\        / /  ____| |    / ____/ __ \\|  \\/  |  ____| |__   __/ __ \\ \n");
    printf("  \\ \\  /\\  / /| |__  | |   | |   | |  | | \\  / | |__       | | | |  | |\n");
    printf("   \\ \\/  \\/ / |  __| | |   | |   | |  | | |\\/| |  __|      | | | |  | |\n");
    printf("    \\  /\\  /  | |____| |___| |___| |__| | |  | | |____     | | | |__| |\n");
    printf(" __  \\/  \\/  _|______|______\\_____\\____/|_|  |_|______|    |_|  \\____/ \n");
    printf(" \\ \\        / / __ \\|  __ \\|  __ \\| | \\ \\   / /                        \n");
    printf("  \\ \\  /\\  / / |  | | |__) | |  | | |  \\ \\_/ /                         \n");
    printf("   \\ \\/  \\/ /| |  | |  _  /| |  | | |   \\   /                          \n");
    printf("    \\  /\\  / | |__| | | \\ \\| |__| | |____| |                           \n");
    printf("     \\/  \\/   \\____/|_|  \\_\\_____/|______|_|                           \n");
    printf(RESET "\n");

    while(guesses < attempts) 
    {
        ft_printf("\nAttempt %d out of ",guesses + 1);
        ft_printf("%d -Enter your guess: ",attempts);
        guess[guesses] = get_next_line(0);
        if(strcmp(guess[guesses],"give up\n") == 0)
        {
            ft_printf("\nToo bad! the choosen word was = %s\n",word);
            freetrix(guess);
            freetrix(words);
            exit(1);
        }
        if(ft_strlen(guess[guesses]) != 6)
        {
            ft_printf("please enter a 5 leter word");
            free(guess[guesses]) ;
            continue;
        }
        if(strcmp(guess[guesses],word) == 0)
        {
            ft_printf("Correct! You win!\n");
            freetrix(guess);
            freetrix(words);
            exit(0);
        }
        print_feedback(guess[guesses],word);
        guesses++;
    }
    ft_printf("\nChoosen word = %s\n",word);
    freetrix(words);
    freetrix(guess);
}
