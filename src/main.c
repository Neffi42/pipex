/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/27 00:12:56 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, const char **av, char **envp)
{
	int		**fd;
	int		controls[4];
	pid_t	pid;

	if (ac < 5)
		error_status(1, ERROR_USAGE, NULL, 0);
	fd = init_fd(ac, av);
	init_controls(controls, ac);
	while (++(controls[0]) < controls[2])
	{
		pid = fork();
		if (pid == -1)
			error_errno(fd, 1);
		if (!pid)
			exec_child(av[controls[0]], envp, fd, controls);
		close_pipes(fd, controls);
		waitpid(pid, &(controls[3]), 0);
		check_wstatus(controls[3], fd);
	}
	close_and_free(fd, 1);
	exit(0);
}
