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