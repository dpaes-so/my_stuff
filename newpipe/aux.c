#include "pipex.h"
char	**path_finder(char **envp, t_pipe pipe)
{
	int		i;
	char	*temp;
	char	**split;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH", 4))
			break ;
	if (!envp[i])
	{
		close(pipe.outfile_fd);
		unlink("here_doc");
		exit(0);
	}
	envp[i] = envp[i] + 5;
	split = ft_split(envp[i], ':');
	i = -1;
	while (split[++i])
	{
		temp = split[i];
		split[i] = ft_strjoin(temp, "/");
		free(temp);
	}
	return (split);
}

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
	int	ret;

	if (pipe->ac < 6)
	{
		ft_putstr_fd("Please input at least 2 commands with here_doc", 2);
		close(pipe->outfile_fd);
		exit(0);
	}
	ret = here_doc(pipe);
	return (ret);
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
	return (fd[0]);
}

void	file_parse(t_pipe *pipex, char **av, int ac)
{
	pipex->ac = ac;
	pipex->av = av;
	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		pipex->infile_fd = here_doc_check(pipex);
		if (pipex->infile_fd < 0)
			exit(1);
		pipex->outfile_fd = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY,
				0644);
		pipex->cmd = 2;
	}
	else
	{
		pipex->infile_fd = open(av[1], O_RDONLY);
		pipex->outfile_fd = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY,
				0644);
		if (pipex->outfile_fd < 0)
			exit(1);
		pipex->cmd = 1;
	}
}