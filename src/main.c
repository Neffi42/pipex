/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/25 20:14:50 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_io(const char *infile, const char *outfile, int *io)
{
	io[0] = open(infile, O_RDONLY);
	if (io[0] == -1)
		error_errno();
	io[1] = open(outfile, O_WRONLY);
	if (io[1] == -1 && close(io[0]))
		error_errno();
	io[3] = dup(STDIN_FILENO);
	if (io[3] == -1 && double_close(io))
		error_errno();
	io[4] = dup(STDOUT_FILENO);
	if (io[4] == -1 && double_close(io))
	{
		close(io[3]);
		error_errno();
	}
	return (0);
}

static	int	double_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (1);
}

static int	execute(char *s, char **envp)
{
	char	**cmd;
	int		status;

	cmd = ft_split(s, ' ');
	if (!cmd)
		error_status(2, ERROR_MALLOC);
	cmd[0] = ft_freejoin("usr/bin/", cmd[0], 1);
	if (!cmd[0] && !ft_free_tab(cmd))
		error_status(2, ERROR_MALLOC);
	status = execve(cmd[0], cmd, envp);
	if (status == -1 && ft_free_tab(cmd))
		exit(status);
}

int	main(int ac, const char **av, char **envp)
{
	int		wstatus;
	int		io[4];
	int		fd[2];
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
		// dup thingy
		dup2(STDOUT_FILENO, io[1]);
		execute(av[2], envp);
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
