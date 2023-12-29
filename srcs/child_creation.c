/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:46:50 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:51:19 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pipes(t_pipex *pipex)
{
	if (!pipex->pipes)
		return ;
	if (pipex->pipe && pipex->pipes[pipex->pipe - 1])
		close(pipex->pipes[pipex->pipe - 1][0]);
	if (pipex->pipes[pipex->pipe])
		close(pipex->pipes[pipex->pipe++][1]);
}

void	child_creation(t_pipex *pipex, int ac, const char **av)
{
	int		i;
	int		wstatus;
	pid_t	pid;

	i = 1 + pipex->here_doc;
	while (++i < ac - 1)
	{
		pipex->cmd = (char *)(av[i]);
		if (!(*(pipex->cmd)))
			error_status(pipex, 13, NULL);
		pid = fork();
		if (pid == -1)
			error_errno(pipex, errno, NULL);
		if (!pid)
			execute(pipex, i, ac - 1);
		close_pipes(pipex);
		wait(&(wstatus));
		check_wstatus(pipex, wstatus);
	}
}
