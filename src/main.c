/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/25 18:41:08 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_io(const char *infile, const char *outfile, int *fd)
{
	fd[0] = open(infile, O_RDONLY);
	if (fd[0] == -1)
		error_errno();
	fd[1] = open(outfile, O_WRONLY);
	if (fd[1] == -1 && close(fd[0]))
		error_errno();
	return (0);
}

static	int	double_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (1);
}

int	main(int ac, const char **av, char **envp)
{
	int		wstatus;
	int		io[2];
	int		fd[2];
	char	**cmd;
	pid_t	pid;

	if (ac < 4)
		error_status(1, ERROR_USAGE);
	open_io(av[1], av[ac - 1], io);
	if (pipe(fd) == -1 && double_close(io))
		error_errno();
	pid = fork();
	if (pid == -1 && double_close(io) && double_close(fd))
		error_errno();
	if (!pid)
	{
		double_close(fd);
		cmd = ft_split(av[2], ' ');
		if (!cmd)
			error_status(2, ERROR_MALLOC);
		cmd[0] = ft_freejoin("usr/bin/", cmd[0], 1);
		if (!cmd[0] && !ft_free_tab(cmd))
			error_status(2, ERROR_MALLOC);
		ft_dprintf(1, "%s\n", cmd[0]);
		wstatus = execve(cmd[0], cmd, envp);
		if (wstatus == -1 && ft_free_tab(cmd))
			exit(wstatus);
	}
	else
	{
		wait(&wstatus);
		double_close(fd);
		double_close(io);
		if (WIFEXITED(wstatus))
		{
			wstatus = WEXITSTATUS(wstatus);
			if (!wstatus)
				ft_dprintf(1, "All smooth\n");
			else
				error_errno();
		}
	}
	exit(0);
}
