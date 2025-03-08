#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define NUM_PLAYERS 4
#define WINNING_POSITION 12
#define NUM_SIMULATIONS 10000000
#define NUM_PROCESSES 4

typedef struct
{
	int	number;
	int	position;
	int	can_move;
}		Player;

int	get_ai_choice(void)
{
	int	choices[3] = {1, 3, 5};
	return (choices[rand() % 3]);
}

int	simulate_bomb(void)
{
	Player	players[NUM_PLAYERS];
	int		i;
	int		j;

	players[0].number = 1;
	i = 0;
	while (i < NUM_PLAYERS)
	{
		players[i].position = 0;
		i++;
	}
	while (1)
	{
		i = 1;
		while (i < NUM_PLAYERS)
		{
			players[i].number = get_ai_choice();
			i++;
		}
		i = 0;
		while (i < NUM_PLAYERS)
		{
			j = 0;
			players[i].can_move = 1;
			while (j < NUM_PLAYERS)
			{
				if (players[i].number == players[j].number && i != j)
					players[i].can_move = 0;
				j++;
			}
			i++;
		}
		i = 0;
		while (i < NUM_PLAYERS)
		{
			if (players[i].can_move == 1)
				players[i].position += players[i].number;
			i++;
		}
		i = 0;
		while (i < NUM_PLAYERS)
		{
			if (players[i].position >= WINNING_POSITION)
			{
				if (i == 0)
					return (1);
				return (0);
			}
			i++;
		}
	}
}

int	main(void)
{
	srand(time(NULL));
	int	result;
    int i;
    int pid[NUM_PROCESSES];
    int status = 0;

    i = 0;
	result = 0;
    while(i < NUM_PROCESSES)
    {
        pid[i] = fork();
        if(pid[i] == 0)
        {
			printf("CHILd made %d\n",i);
            int procces;
            int child_result;
            
            child_result = 0;
            procces = 0;
            while(procces < NUM_SIMULATIONS/NUM_PROCESSES)
            {
	            child_result += simulate_bomb();
                procces++;
            }
            exit(child_result);
        }
        i++;
    }
    i = 0;
    while (i < NUM_PROCESSES)
    {
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status))
            result += WEXITSTATUS(status);
        else
            printf("ONE CHILD COMMITEDF SUICIDE");
        i++;
    }
	printf("REAL PLAYER WON %d TIMES", result);
	return (0);
}
