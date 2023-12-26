/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 19:16:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_child(const char *cmd, char **envp, int **fd, int *controls)
{
	if (controls[0] > 2)
		redirect_fd(fd[controls[2]], 0, 2, fd[0][0]);
	if (controls[0] + 1 < controls[1])
		redirect_fd(fd[controls[2]], 1, 2, fd[0][1]);
	execute(cmd, envp, fd);
}

static void	init_controls(int *controls, int ac)
{
	controls[0] = 1;
	controls[1] = ac - 1;
	controls[2] = 1;
	controls[3] = 0;
}

static void	close_pipe(int **fd, int *controls, int ac)
{
	if (controls[0] == 2)
		close(fd[0][0]);
	else if (controls[0] > 2 && controls[2] < ac - 3)
		close_nfd(fd[controls[2]++], 2);
}

int	main(int ac, const char **av, char **envp)
{
	int		**fd;
	int		controls[4];
	pid_t	pid;

	if (ac < 5)
		error_status(1, ERROR_USAGE, NULL, 0);
	fd = init_fd(ac, av);
	init_controls(controls, ac);
	while (++(controls[0]) < controls[1])
	{
		pid = fork();
		if (pid == -1)
			error_errno(fd, 1);
		if (!pid)
			exec_child(av[controls[0]], envp, fd, controls);
		close_pipe(fd, controls, ac);
		waitpid(pid, &(controls[3]), 0);
		check_wstatus(controls[3], fd);
	}
	close_and_free(fd, 1);
	exit(0);
}
