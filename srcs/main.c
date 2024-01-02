/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 10:50:21 by abasdere         ###   ########.fr       */
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

static pid_t	call_cmds(t_pipex *pipex, int ac, const char **av)
{
	pid_t	pid;
	int		i;

	i = 1 + pipex->here_doc;
	while (++i < ac - 1)
	{
		pipex->cmd = (char *)(av[i]);
		pid = fork();
		if (pid == -1 && close_and_free(pipex))
			return (perror(PNAME), errno);
		if (!pid)
			execute(pipex, i, ac - 1);
		close_pipes(pipex);
	}
	close_and_free(pipex);
	return (pid);
}

static int	wait_processes(pid_t pid)
{
	int	wstatus;
	int	x;

	x = EXIT_FAILURE;
	if (pid == EXIT_FAILURE)
		return (x);
	while (errno != ECHILD)
	{
		if (wait(&wstatus) == pid)
		{
			if (WIFEXITED(wstatus))
				x = WEXITSTATUS(wstatus);
			else
				x = 128 + WTERMSIG(wstatus);
		}
	}
	return (x);
}

int	main(int ac, const char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
		error(EXIT_FAILURE, PNAME, ERROR_USAGE);
	init_pipex(&pipex, ac, av, envp);
	return (wait_processes(call_cmds(&pipex, ac, av)));
}
