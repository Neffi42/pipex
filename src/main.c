/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 15:17:25 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_io(const char *infile, const char *outfile)
{
	int	io[2];

	io[0] = open(infile, O_RDONLY);
	if (io[0] == -1)
		error_errno();
	io[1] = open(outfile, O_WRONLY);
	if (io[1] == -1 && close_nfd(io, 1))
		error_errno();
	redirect_fd(io, 0, 2, STDIN_FILENO);
	redirect_fd(io, 1, 2, STDOUT_FILENO);
}

static void	call_cmd(const char **cmd, char **envp, int *fd, int *nb_pipes)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1 && close_nfd(fd, 2))
		error_errno();
	if (!pid)
	{
		if (nb_pipes[0] + 1 < nb_pipes[1])
			redirect_fd(fd, 1, 2, STDOUT_FILENO);
		close_nfd(fd, 2);
		execute(cmd[nb_pipes[0]], envp);
	}
	wait(&wstatus);
	if (!WIFEXITED(wstatus))
		error_status(3, ERROR_WSTATUS);
	wstatus = WEXITSTATUS(wstatus);
	if (wstatus)
		exit(wstatus);
	if (++(nb_pipes[0]) < nb_pipes[1] && redirect_fd(fd, 0, 2, STDIN_FILENO))
		call_cmd(cmd, envp, fd, nb_pipes);
}

int	main(int ac, const char **av, char **envp)
{
	int	fd[2];
	int	nb_pipes[2];

	if (ac < 5)
		error_status(1, ERROR_USAGE);
	redirect_io(av[1], av[ac - 1]);
	if (pipe(fd) == -1)
		error_errno();
	nb_pipes[0] = 2;
	nb_pipes[1] = ac - 1;
	call_cmd(av, envp, fd, nb_pipes);
	close_nfd(fd, 2);
	exit(0);
}
