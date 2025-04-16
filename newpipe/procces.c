/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:14:09 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/04/16 19:15:43 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_exit(char *exec, t_pipe *pipe, char **argument_list)
{
	if (access(exec, F_OK) < 0)
	{
		ft_putstr_fd("Pipex: Command not found\n", 2);
		dprintf(2,"exec = %s\n",exec);
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
		dprintf(2,"exec = %s\n",exec);
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
		if (pipe->path != NULL && pipe->path[i] && (access(str, F_OK) < 0 ))
			exec = ft_strjoin(pipe->path[i], argument_list[0]);
		else
		{
			exec = ft_strdup(argument_list[0]);
			flag = 1;
		}
		dprintf(2,"exec = %s\n",exec);
		execve(exec, argument_list, envp);
		i++;
	}
	cmd_exit(exec, pipe, argument_list);
}

void	first_child(t_pipe *pipex, char **ev)
{
	if(access(pipex->av[1],F_OK | R_OK))
	{
		close(pipex->pipefd[1]);
		close(pipex->outfile_fd);
		freetrix(pipex->path);
		exit(1);
	}
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	dup2(pipex->infile_fd, STDIN_FILENO);
	close(pipex->pipefd[1]);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	cmdexec(pipex, ev, pipex->av[pipex->cmd]);
}
void	last_child(t_pipe *pipex, char **ev)
{
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	close(pipex->pipefd[1]);
	close(pipex->outfile_fd);
	cmdexec(pipex, ev, pipex->av[pipex->cmd]);
}

void	middle_child(t_pipe *pipex, char **ev)
{
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close(pipex->pipefd[1]);
	close(pipex->outfile_fd);
	cmdexec(pipex, ev, pipex->av[pipex->cmd]);
}
