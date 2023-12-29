/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:39:46 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 02:36:31 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	redirect_fd(t_pipex *pipex, int newfd, int oldfd)
{
	int	fd2;

	fd2 = dup2(newfd, oldfd);
	if (fd2 == -1)
		error_errno(pipex, errno, "redirect_fd");
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

static void	execute(t_pipex *pipex)
{
	size_t	i;
	char	**tab;
	char	*cmd;

	i = -1;
	tab = ft_split(pipex->cmd, ' ');
	if (!tab)
		error_status(pipex, CODE_MALLOC, "ft_split");
	while (pipex->path[++(i)])
	{
		cmd = init_cmd(pipex->path[i], tab[0]);
		if (!cmd && !ft_free_tab(tab))
			error_status(pipex, CODE_MALLOC, "init_cmd");
		if (!access(cmd, X_OK))
			execve(cmd, tab, pipex->envp);
		free(cmd);
	}
	print_error(pipex->pname, ERROR_CMD, tab[0]);
	ft_free_tab(tab);
	exit(close_and_free(pipex));
}

void	call_exec(t_pipex *pipex, int index, int end)
{
	size_t	i;

	i = -1;
	if (index == 2)
		redirect_fd(pipex, pipex->infile, STDIN_FILENO);
	else
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
	execute(pipex);
}
