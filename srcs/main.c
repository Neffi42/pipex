/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 14:41:54 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*init_cmd(char *path, char *cmd_name)
{
	char	*cmd;

	cmd = ft_strjoin(path, "/");
	if (!cmd)
		return (NULL);
	cmd = ft_freejoin(cmd, cmd_name, -1);
	if (!cmd)
		return (NULL);
	return (cmd);
}

static void	execute(t_pipex *pipex, int in, int out)
{
	size_t	i;
	char	**tab;
	char	*cmd;

	if (dup2(in, STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
		(perror(PNAME), close(in), close(out), free_all(pipex), exit(errno));
	(close(in), close(out), i = -1);
	tab = ft_split(pipex->cmd, ' ');
	if (!tab)
		(perror(PNAME), free_all(pipex), exit(errno));
	while (pipex->path[++(i)])
	{
		cmd = init_cmd(pipex->path[i], tab[0]);
		if (!cmd)
			(perror(PNAME), ft_free_tab(tab), free_all(pipex), exit(errno));
		if (!access(cmd, X_OK))
			execve(cmd, tab, pipex->envp);
		free(cmd);
	}
	(ft_free_tab(tab), free_all(pipex));
	exit(error(CODE_CMD, PNAME, ERROR_CMD));
}

static pid_t	call_cmds(t_pipex *pipex, int ac, const char **av, int start)
{
	pid_t	pid;
	int		i;
	int		tab[2];

	i = 0;
	while (++start < ac - 1)
	{
		pipex->cmd = (char *)(av[start]);
		pid = fork();
		if (pid == -1)
			(perror(PNAME), free_all(pipex), exit(errno));
		if (!pid)
		{
			if (start == 2 + pipex->here_doc)
				tab[0] = pipex->infile;
			else
				tab[0] = pipex->pipes[i++][0];
			if (start == ac - 2)
				tab[1] = pipex->outfile;
			else
				tab[1] = pipex->pipes[i][1];
			execute(pipex, tab[0], tab[1]);
		}
	}
	return (free_all(pipex), pid);
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
	return (wait_processes(call_cmds(&pipex, ac, av, 1 + pipex.here_doc)));
}
