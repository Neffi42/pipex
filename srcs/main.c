/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 21:17:01 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*init_cmd(char **path, char *cmd_name)
{
	char	*cmd;
	int		i;

	if (!access(cmd_name, X_OK))
		return (cmd_name);
	i = -1;
	while (path[++i])
	{
		cmd = ft_freejoin(ft_strjoin(path[i], "/"), cmd_name, -1);
		if (!cmd)
			return (NULL);
		if (!access(cmd, X_OK))
			return (cmd);
		free(cmd);
	}
	return (cmd_name);
}

static void	execute(t_pipex *pipex, int *fd)
{
	char	**args;
	char	*cmd;

	fd[3] = dup2(fd[0], STDIN_FILENO);
	fd[4] = dup2(fd[1], STDOUT_FILENO);
	if (fd[3] == -1 || fd[4] == -1)
		(perror("dup2"), close(fd[3]), close(fd[4]), free_all(pipex), \
		exit(errno));
	(close_all(pipex), args = ft_split(pipex->cmd, ' '));
	if (!args)
		(ft_dprintf(2, "%s", ERR_MEM), close(fd[3]), close(fd[4]), \
		free_all(pipex), exit(-1));
	cmd = pipex->cmd;
	if (args[0])
		cmd = init_cmd(pipex->path, args[0]);
	if (!cmd)
		(ft_dprintf(2, "%s", ERR_MEM), \
		ft_free_tab(args), close(fd[3]), close(fd[4]), free_all(pipex), \
		exit(-1));
	execve(cmd, args, pipex->envp);
	if (cmd == pipex->cmd)
		ft_dprintf(2, "%s: %s", cmd, ERR_CMD);
	else
		ft_dprintf(2, "%s: %s", args[0], ERR_CMD);
	(free_all(pipex), close(fd[3]), close(fd[4]), ft_free_tab(args), exit(127));
}

static pid_t	call_cmds(t_pipex *pipex, char **cmds)
{
	pid_t	pid;
	int		i;
	int		fd[4];

	i = -1;
	while (++i <= pipex->nb_pipes)
	{
		pipex->cmd = *(cmds++);
		pid = fork();
		if (pid == -1)
			(perror("fork"), free_all(pipex), exit(errno));
		if (!pid)
		{
			if (!i)
				fd[0] = pipex->infile;
			else
				fd[0] = pipex->pipes[i - 1][0];
			if (i == pipex->nb_pipes)
				fd[1] = pipex->outfile;
			else
				fd[1] = pipex->pipes[i][1];
			execute(pipex, fd);
		}
	}
	return (free_all(pipex), pid);
}

static int	wait_childs(pid_t pid)
{
	int	wstatus;
	int	x;

	x = EXIT_FAILURE;
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
		(ft_dprintf(2, "%s", ERR_ARGS), exit(-1));
	init_pipex(&pipex, ac, av, envp);
	return (wait_childs(call_cmds(&pipex, (char **)(av + 2 + pipex.here_doc))));
}
