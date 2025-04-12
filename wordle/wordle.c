#include "wordle.h"
int get_word(char *input,char ***words,char **list)
{
    int fd;
    int i;
    char *str;
    char *wlist;
    char *temp;

    // (void)wlist;
    i = 0;
    temp = malloc(sizeof(char) * ft_strlen(input));
    while(input[i] && input[i] != '\n')
    {
        temp[i] = input[i];
        i++;
    }
    temp[i] = '\0';
    wlist = ft_strjoin(temp,".txt");
    i = 0;
    while(list[i])
    {
        if(ft_strncmp(wlist,list[i],ft_strlen(wlist)) == 0)
            break;
        i++;
    }
    // if(ft_strncmp(input,"daily",5) == 0)
    // {
    //     free(wlist);
    //     free(temp);
    //     return(2);
    // }
    if(!list[i])
    {
        printf("invalid list name\n");
        free(wlist);
        free(temp);
        return(-1);
    }
    fd = open(wlist,O_RDONLY);
    if(fd < 0)
    {
        ft_printf("FAILED TO OPEN THE WORD LIST\n");
        free(wlist);
        free(temp);
        return(-1);
    }
    i = 0;
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
    free(wlist);
    free(temp);
    return(i);
}

void print_feedback(char *guess, char *word)
{
    int i;
    int len;
    int key;
    char letter;
    int letter_count[26] = {0};
    int j = 0;
    int check;
    int flag;
    static char keyboard[26] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    key = 0;
    i = 0;
    len = ft_strlen(word);
    while (j < len - 1)
    {
        letter_count[word[j] - 'a']++;
        // printf("letter count %c is %d\n",word[j],letter_count[word[j] - 'a']);
        j++;
    }
    while(i < len - 1)
    {
        flag = 1;
        key = 0;
        if(guess[i] >= 'a' && guess[i] <= 'z')
            letter = guess[i] - 32;
        else
            letter = guess[i];
        // printf("letter = %c\n",letter);
        while( key < 26 && letter != keyboard[key])
            key++;
        if(key < 26)
            keyboard[key] = '0';

        if(guess[i] == word[i])
        {
            printf(GREEN "%c" RESET, letter);
            letter_count[guess[i] - 'a']--;
        }
        else if(ft_strchr(word,guess[i]) && letter_count[guess[i] - 'a'] > 0 && flag)
        {
            check = i;
            while(check < len - 1)
            {
                if(guess[check] == word[check])
                {
                    if(letter_count[guess[i] - 'a'] < 2)
                        flag = 0;
                }
                check++;
            }
            if(!flag)
                printf(RED "%c" RESET,letter);
            else
            {
                printf(YELLOW "%c" RESET,letter);
                letter_count[guess[i] - 'a']--;
            }
        }
        else
            printf(RED "%c" RESET,letter);
        i++;
    }

    printf("\n\n");
    i = 0;
    while(i < 26)
    {
        if(keyboard[i] != '0')
            printf("%c",keyboard[i]);
        else
            printf(" ");
        printf("   ");
        if(i == 10 || i == 20)
            printf("\n");
        i++;
    }
    printf("\n");
}

// char *get_daily_word(char **word_list)
// {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);

//     // (void)word_list;
//     // Get the current date (ignoring time) as a single value
//     struct tm *tm_info = localtime(&tv.tv_sec);
//     int year = tm_info->tm_year + 1900;  // tm_year is years since 1900
//     int month = tm_info->tm_mon + 1;     // tm_mon is 0-based
//     int day = tm_info->tm_mday;

//     // Combine year, month, and day to get a unique number for the day
//     unsigned int daily_value = year * 10000 + month * 100 + day;
//     srand(daily_value);

//     int index = rand() % MAX_WORDS;

//     return word_list[index];
//     // return("mango\n");
// }

int main()
{
    char **words;
    char *word;
    int guesses = 0;
    char *cgame_mode;
    int attempts = 6;//HOW MANY ATTEMPS MAX TO GUESS THE WORD
    char **guess = ft_calloc(attempts,sizeof(char *));
    int i =-1;
    char *games[26] = {"animal.txt","words.txt"};
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

    ft_printf("\nCHOOSE GAME MODE!\n\n");
    while(games[++i])
        ft_printf("%s   ",games[i]);
    ft_printf("\n\n->");
    cgame_mode = get_next_line(0);
    int word_count = get_word(cgame_mode,&words,games);
    if(word_count < 0)
    {
        freetrix(guess);
        free(cgame_mode);
        exit(1);
    }
    // if(ft_strncmp(cgame_mode,"daily",5) == 0)
    //     word = get_daily_word(words);
    // else
    // {
        srand(time(NULL));
        word = words[rand() % word_count];
    // }

    while(guesses < attempts) 
    {
        ft_printf("\nAttempt %d out of ",guesses + 1);
        ft_printf("%d -Enter your guess: ",attempts);
        guess[guesses] = get_next_line(0);
        if(strcmp(guess[guesses],"give up\n") == 0)
        {
            ft_printf("\nToo bad! the choosen word was = %s\n",word);
            freetrix(guess);
            free(cgame_mode);
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
            // if(ft_strncmp(cgame_mode,"daily",5) != 0)
            freetrix(words);
            free(cgame_mode);
            exit(0);
        }
        print_feedback(guess[guesses],word);
        guesses++;
    }
    ft_printf("\nChoosen word = %s\n",word);
    freetrix(words);
    freetrix(guess);
    free(cgame_mode);
}
