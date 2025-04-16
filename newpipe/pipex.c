#include "pipex.h"


void	freetrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}


int	here_doc_check(t_pipe *pipe)
{
    int ret;

	if (pipe->ac < 6)
	{
		ft_putstr_fd("Please input at least 2 commands with here_doc", 2);
		close(pipe->outfile_fd);
		exit(0);
	}
	ret = here_doc(pipe);
    return(ret);
}

int	here_doc(t_pipe *pipex)
{
	char	*str;
	int		fd[2];
	int		i;

    pipe(fd);
	while (1)
	{
		i = 0;
		str = get_next_line(0);
		if (!str || !ft_strncmp(str, pipex->av[2], ft_strlen(pipex->av[2])))
		{
			free(str);
			break ;
		}
		while (str[i])
			write(fd[1], &str[i++], 1);
		free(str);
	}
    close(fd[1]);
	return(fd[0]);
}


void	file_parse(t_pipe *pipex, char **av,int ac)
{
	pipex->ac = ac;
	pipex->av = av;

	if(ft_strncmp("here_doc",av[1],8) == 0)
    {
        pipex->infile_fd = here_doc_check(pipex);
        if(pipex->infile_fd < 0)
            exit(1);
        pipex->outfile_fd =  open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
        pipex->cmd = 2;
    }
    else
    {  
        pipex->infile_fd = open(av[1],O_RDONLY);
        pipex->outfile_fd =  open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
        if (pipex->infile_fd < 0 || pipex->outfile_fd < 0)
		    exit(1);
        pipex->cmd = 1;
    }
}

void	cmd_exit(char *exec, t_pipe *pipe, char **argument_list)
{
	if (access(exec, F_OK) < 0)
	{
		ft_putstr_fd("Pipex: Command not found\n", 2);
		freetrix(argument_list);
		freetrix(pipe->path);
		close(pipe->outfile_fd);
		if (exec)
			free(exec);
		exit(127);
	}
	if (access(exec, X_OK) < 0)
	{
		ft_putstr_fd("Permission denied\n", 2);
		freetrix(argument_list);
		freetrix(pipe->path);
		close(pipe->outfile_fd);
		if (exec)
			free(exec);
		exit(126);
	}
}

void	cmdexec(t_pipe *pipe, char *envp[], char *str)
{
	int		i;
	char	*exec;
	char	**argument_list;
	int		flag;

	flag = 0;
	i = 0;
	argument_list = ft_arg_split(str, ' ');
	while (flag == 0 && argument_list[0])
	{
		if (i > 0)
			free(exec);
		if (pipe->path != NULL  && pipe->path[i] && access(str, F_OK) < 0)
			exec = ft_strjoin(pipe->path[i], argument_list[0]);
		else
		{
			exec = ft_strdup(argument_list[0]);
			flag = 1;
		}
		execve(exec, argument_list, envp);
		i++;
	}
	cmd_exit(exec, pipe, argument_list);
}

void first_child(t_pipe *pipex,char **ev)
{
    dup2(pipex->pipefd[1],STDOUT_FILENO);
    dup2(pipex->infile_fd,STDIN_FILENO);
    close(pipex->pipefd[1]);
    close(pipex->infile_fd);
    close(pipex->outfile_fd);
    cmdexec(pipex,ev,pipex->av[pipex->cmd]);
}
void last_child(t_pipe *pipex,char **ev)
{
    dup2(pipex->outfile_fd,STDOUT_FILENO);
    close(pipex->pipefd[1]);
    close(pipex->outfile_fd);
    cmdexec(pipex,ev,pipex->av[pipex->cmd]);
}

void middle_child(t_pipe *pipex,char **ev)
{
    dup2(pipex->pipefd[1],STDOUT_FILENO);
    close(pipex->pipefd[1]);
    close(pipex->outfile_fd);
    cmdexec(pipex,ev,pipex->av[pipex->cmd]);
}
void which_child(t_pipe *pipex,char **ev)
{
    pipex->pid1 = fork();
    if(pipex->pid1 < 0)
        exit(1);
    if(pipex->pid1 == 0)
    {
        close(pipex->pipefd[0]);
		if (pipex->cmd== !(ft_strncmp("here_doc", pipex->av[1], -1)) + 2)
			first_child(pipex,ev);
		else if (pipex->cmd == pipex->ac - 2)
			last_child(pipex,ev);
		else
			middle_child(pipex,ev);
    }
    else
    {
        if (pipex->cmd== !(ft_strncmp("here_doc", pipex->av[1], -1)) + 2)
            close(pipex->infile_fd);
        else if (pipex->cmd == pipex->ac -2)
            close(pipex->outfile_fd);
        close(pipex->pipefd[1]);
        dup2(pipex->pipefd[0],STDIN_FILENO);
        close(pipex->pipefd[0]);
    }
}
void ft_pipex(t_pipe pipex,char **ev)
{
    // ft_printf("HERE\n");
    if(pipe(pipex.pipefd) == 0)
        which_child(&pipex,ev);
    else
    {
        ft_putstr_fd("Error, Pipe faield",2);
        exit(1);
    }
}
void wait_child(t_pipe *pipex)
{
    int i;
    int status;

    i = !(ft_strncmp("here_doc", pipex->av[1], -1));
    while(i < pipex->cmd)
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
        file_parse(&pipex,av,ac);
        pipex.path = path_finder(env,pipex);
        // printf("%d\n\n",pipex.cmd);
        while(++pipex.cmd < ac - 1)
            ft_pipex(pipex,env);
        wait_child(&pipex);
		freetrix(pipex.path);
        exit(pipex.status);
	}
	else
		ft_putstr_fd("Please input 5 arguments ", 2);
	return (0);
}
