/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 01:17:41 by abasdere         ###   ########.fr       */
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
		if (!(*(pipex->cmd)))
			error(pipex, CODE_PERM, NULL);
		pid = fork();
		if (pid == -1)
			return (perror(PNAME), (void)close_and_free(pipex), errno);
		if (!pid)
			execute(pipex, i, ac - 1);
		close_pipes(pipex);
		ft_dprintf(STDERR_FILENO, "pid:%d\n", getpid());
	}
	return (pid);
}

static int	check_wstatus(int wstatus, int end)
{
	static int	procces_terminated;
	int			status_code;

	if (!WIFEXITED(wstatus) && wait_all(procces_terminated, end))
		return (CODE_WSTATUS);
	status_code = WEXITSTATUS(wstatus);
	if (status_code && wait_all(procces_terminated, end))
		return (status_code);
	procces_terminated++;
	return (EXIT_SUCCESS);
}

int	main(int ac, const char **av, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		wstatus[2];
	pid_t	pid;

	if (ac < 5)
		error(NULL, CODE_USAGE, NULL);
	init_pipex(&pipex, ac, av, envp);
	call_cmds(&pipex, ac, av);
	pid = call_cmds(&pipex, ac, av);
	i = 2 + pipex.here_doc;
	waitpid(pid, &(wstatus[1]), 1);
	wstatus[1] = check_wstatus(wstatus[1], ac - 1 - i);
	while (++i < ac - 1 && wait(&(wstatus[0])))
		check_wstatus(wstatus[0], ac - 1 - i);
	close_and_free(&pipex);
	return (wstatus[1]);
}
