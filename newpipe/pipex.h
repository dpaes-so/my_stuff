/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:23:36 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/04/16 19:19:32 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "includes/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		ac;
	int 	cmd;
	int		pid1;
	int		infile_fd;
	int		outfile_fd;
	int		pipefd[2];
	int 	status;
	char	**av;
	char	**path;
}			t_pipe;

//arg_split
char	**ft_arg_split(char const *s, char c);
//pipex
void	which_child(t_pipe *pipex, char **ev);
void	ft_pipex(t_pipe pipex, char **ev);
void	wait_child(t_pipe *pipex);
//process
void	cmdexec(t_pipe *pipe, char *envp[], char *str);
void	first_child(t_pipe *pipex, char **ev);
void	last_child(t_pipe *pipex, char **ev);
void	middle_child(t_pipe *pipex, char **ev);
void	cmd_exit(char *exec, t_pipe *pipe, char **argument_list);
//aux
void	file_parse(t_pipe *pipex, char **av,int ac);
char	**path_finder(char **envp, t_pipe pipe);
void	freetrix(char **matrix);
int	here_doc_check(t_pipe *pipe);
int	here_doc(t_pipe *pipex);
#endif