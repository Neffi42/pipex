/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 12:41:00 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	close_nfd(int *fd, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		close(fd[i]);
	return (1);
}

static void	open_io(const char *infile, const char *outfile, int *io2)
{
	int	io[2];

	io[0] = open(infile, O_RDONLY);
	if (io[0] == -1)
		error_errno();
	io[1] = open(outfile, O_WRONLY);
	if (io[1] == -1 && !close(io[0]))
		error_errno();
	io2[0] = dup(STDIN_FILENO);
	if (io2[0] == -1 && close_nfd(io, 2))
		error_errno();
	io2[1] = dup(STDOUT_FILENO);
	if (io2[1] == -1 && close_nfd(io, 2) && !close(io2[0]))
		error_errno();
	io2[2] = dup2(io[0], STDIN_FILENO);
	if (io2[0] == -1 && close_nfd(io, 2) && close_nfd(io2, 2))
		error_errno();
	io2[3] = dup2(io[1], STDOUT_FILENO);
	if (close_nfd(io, 2) && io2[1] == -1 && close_nfd(io2, 3))
		error_errno();
}

static int	execute(const char *cmd, char **envp)
{
	char	**tab;
	int		status;

	tab = ft_split(cmd, ' ');
	if (!tab)
		error_status(2, ERROR_MALLOC);
	tab[0] = ft_freejoin("/usr/bin/", tab[0], 1);
	if (!tab[0] && !ft_free_tab(tab))
		error_status(2, ERROR_MALLOC);
	status = execve(tab[0], tab, envp);
	ft_free_tab(tab);
	exit(status);
}

static void	call_cmd(const char *cmd, char **envp, int *io, int *fd)
{
	int		wstatus;
	pid_t	pid;

	pid = fork();
	if (pid == -1 && close_nfd(io, 4) && close_nfd(fd, 2))
		error_errno();
	if (!pid)
	{
		execute(cmd, envp);
	}
	else
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus))
			exit(WEXITSTATUS(wstatus));
		error_status(3, ERROR_WSTATUS);
	}
}

int	main(int ac, const char **av, char **envp)
{
	int	io[4];
	int	fd[2];
	int	i;

	if (ac < 5)
		error_status(1, ERROR_USAGE);
	open_io(av[1], av[ac - 1], io);
	if (pipe(fd) == -1 && close_nfd(io, 4))
		error_errno();
	i = 1;
	while (++i < ac - 1)
		call_cmd(av[i], envp, io, fd);
	close_nfd(fd, 2);
	close_nfd(io, 4);
	exit(0);
}
