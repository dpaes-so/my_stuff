/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:23:36 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/04/02 19:08:50 by dpaes-so         ###   ########.fr       */
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


int	here_doc_check(t_pipe *pipe);

int	here_doc(t_pipe *pipex);

void	file_parse(t_pipe *pipex, char **av,int ac);

char	**ft_arg_split(char const *s, char c);
char	**path_finder(char **envp, t_pipe pipe);
#endif