#include "pipex.h"

void	which_child(t_pipe *pipex, char **ev)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		exit(1);
	if (pipex->pid1 == 0)
	{
		close(pipex->pipefd[0]);
		if (pipex->cmd == !(ft_strncmp("here_doc", pipex->av[1], -1)) + 2)
			first_child(pipex, ev);
		else if (pipex->cmd == pipex->ac - 2)
			last_child(pipex, ev);
		else
			middle_child(pipex, ev);
	}
	else
	{
		if (pipex->cmd == !(ft_strncmp("here_doc", pipex->av[1], -1)) + 2 && pipex->infile_fd > 0)
			close(pipex->infile_fd);
		else if (pipex->cmd == pipex->ac - 2)
			close(pipex->outfile_fd);
		close(pipex->pipefd[1]);
		dup2(pipex->pipefd[0], STDIN_FILENO);
		close(pipex->pipefd[0]);
	}
}
void	ft_pipex(t_pipe pipex, char **ev)
{
	if (pipe(pipex.pipefd) == 0)
		which_child(&pipex, ev);
	else
	{
		ft_putstr_fd("Error, Pipe faield", 2);
		exit(1);
	}
}
void	wait_child(t_pipe *pipex)
{
	int	i;
	int	status;

	i = !(ft_strncmp("here_doc", pipex->av[1], -1));
	while (i < pipex->cmd)
	{
		wait(&status);
		if (WIFEXITED(status))
			pipex->status = WEXITSTATUS(status);
		i++;
	}
}

int	main(int ac, char **av, char *env[])
{
	t_pipe	pipex;

	(void)env;
	if (ac > 4)
	{
		file_parse(&pipex, av, ac);
		pipex.path = path_finder(env, pipex);
		while (++pipex.cmd < ac - 1)
			ft_pipex(pipex, env);
		wait_child(&pipex);
		freetrix(pipex.path);
		exit(pipex.status);
	}
	else
		ft_putstr_fd("Please input 5 arguments ", 2);
	return (0);
}
