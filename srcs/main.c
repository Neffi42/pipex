/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 03:01:28 by abasdere         ###   ########.fr       */
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

static void	check_wstatus(t_pipex *pipex, int wstatus)
{
	int	status_code;

	if (!WIFEXITED(wstatus) && ft_dprintf(2, "TSET\n"))
		error_errno(pipex, wstatus, NULL);
	status_code = WEXITSTATUS(wstatus);
	if (status_code && close_and_free(pipex))
		exit(status_code);
}

static void	child_creation(t_pipex *pipex, const char **av, int end)
{
	int		i;
	int		wstatus;
	pid_t	pid;

	i = 1;
	while (++i < end)
	{
		pipex->cmd = (char *)(av[i]);
		if (!(*(pipex->cmd)))
			error_status(pipex, 13, NULL);
		pid = fork();
		if (pid == -1)
			error_errno(pipex, errno, NULL);
		if (!pid)
			call_exec(pipex, i, end);
		close_pipes(pipex);
		wait(&(wstatus));
		check_wstatus(pipex, wstatus);
	}
}

int	main(int ac, const char **av, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex, ac, av, envp);
	if (ac < 3)
		error_status(&pipex, CODE_USAGE, NULL);
	if (pipex.nb_pipes < 0)
		copy_file(&pipex);
	child_creation(&pipex, av, ac - 1);
	close_and_free(&pipex);
	exit(EXIT_SUCCESS);
}
