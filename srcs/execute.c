/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:39:46 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 10:55:38 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	redirect_fd(t_pipex *pipex, int newfd, int oldfd)
{
	int	fd2;

	fd2 = dup2(newfd, oldfd);
	if (fd2 == -1 && !close_and_free(pipex))
	{
		perror(PNAME);
		exit(errno);
	}
	return (fd2);
}

static char	*init_cmd(char *path, char *cmd_name)
{
	char	*cmd;

	cmd = ft_strjoin(path, "/");
	if (!cmd)
		return (NULL);
	cmd = ft_freejoin(cmd, cmd_name, -1);
	if (!cmd)
		return (NULL);
	return (cmd);
}

static int	execute(t_pipex *pipex)
{
	size_t	i;
	char	**tab;
	char	*cmd;

	i = -1;
	tab = ft_split(pipex->cmd, ' ');
	if (!tab && close_and_free(pipex))
		return (perror(PNAME), errno);
	while (pipex->path[++(i)])
	{
		cmd = init_cmd(pipex->path[i], tab[0]);
		if (!cmd && !ft_free_tab(tab))
			return (perror(PNAME), (void)close_and_free(pipex), errno);
		if (!access(cmd, X_OK))
			execve(cmd, tab, pipex->envp);
		free(cmd);
	}
	return ((void)ft_free_tab(tab), (void)close_and_free(pipex), \
	error(CODE_CMD, PNAME, ERROR_CMD));
}

void	call_cmd(t_pipex *pipex, int index, int end)
{
	size_t	i;

	i = -1;
	if (index == 2 && !pipex->here_doc)
		redirect_fd(pipex, pipex->infile, STDIN_FILENO);
	else if (!(index == 3 && pipex->here_doc))
		redirect_fd(pipex, pipex->pipes[pipex->pipe - 1][0], STDIN_FILENO);
	if (index + 1 == end)
		redirect_fd(pipex, pipex->outfile, STDOUT_FILENO);
	else
		redirect_fd(pipex, pipex->pipes[pipex->pipe][1], STDOUT_FILENO);
	while (pipex->pipes && pipex->pipes[++i])
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
	}
	exit(execute(pipex));
}
