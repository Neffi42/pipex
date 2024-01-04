/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/04 15:21:10 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*init_cmd(t_pipex *pipex, char *s)
{
	char	*cmd;
	int		i;

	if (ft_strchr(s, '/') != NULL && access(s, F_OK | X_OK) == 0)
		return (s);
	else if (ft_strchr(s, '/') != NULL && access(s, F_OK | X_OK) != 0)
		return ((void)ft_dprintf(2, "%s: %s", pipex->cmd[0], ERR_CMD), NULL);
	i = -1;
	while (pipex->path && pipex->path[++i])
	{
		cmd = ft_freejoin(ft_strjoin(pipex->path[i], "/"), s, -1);
		if (!cmd)
			(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex, 0), exit(-1));
		if (!access(cmd, X_OK))
			return (cmd);
		free(cmd);
	}
	return ((void)ft_dprintf(2, "%s: %s", pipex->cmd[0], ERR_CMD), NULL);
}

static void	execute(t_pipex *pipex, int *fd)
{
	char	*cmd;

	if (!pipex->cmd[0] || !pipex->cmd[0][0])
		(ft_dprintf(2, "%s: %s", pipex->cmd, ERR_CMD), \
		free_all(pipex, 0), exit(127));
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		(perror("dup2"), free_all(pipex, 0), exit(errno));
	(free_all(pipex, 1), cmd = init_cmd(pipex, pipex->cmd[0]));
	if (!cmd)
		(free_all(pipex, 0), exit(127));
	execve(cmd, pipex->cmd, pipex->envp);
	(ft_dprintf(2, "%s: %s", pipex->cmd[0], ERR_CMD), free_all(pipex, 0));
	exit(127);
}

static pid_t	call_cmds(t_pipex *pipex, char **cmds)
{
	pid_t	pid;
	int		i;
	int		fd[2];

	i = -1;
	while (++i <= pipex->nb_pipes && ft_free_tab(pipex->cmd))
	{
		pipex->cmd = ft_split(*(cmds++), ' ');
		if (!pipex->cmd)
			(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex, 0), exit(-1));
		pid = fork();
		if (pid == -1)
			(perror("fork"), free_all(pipex, 0), exit(errno));
		if (!pid)
		{
			fd[0] = pipex->pipes[i - 1][0];
			if (!i)
				fd[0] = pipex->infile;
			fd[1] = pipex->pipes[i][1];
			if (i == pipex->nb_pipes)
				fd[1] = pipex->outfile;
			execute(pipex, fd);
		}
	}
	return (free_all(pipex, 0), pid);
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
	char	*line;
	int		fd;

	if (ac < 5)
		(ft_dprintf(2, "%s", ERR_ARGS), exit(-1));
	pipex.here_doc = !ft_strncmp(av[1], "here_doc", ft_strlen("here_doc"));
	if (pipex.here_doc && ac < 6)
		(ft_dprintf(2, "%s", ERR_BONUS), exit(-1));
	init_pipex(&pipex, ac, av, envp);
	if (pipex.here_doc)
	{
		fd = find_heredoc(&pipex);
		while (ft_printf("here_doc> ") && ft_oget_next_line(0, &line))
		{
			if (!ft_strncmp(pipex.limiter, line, ft_strlen(pipex.limiter)))
				break ;
			(ft_putstr_fd(line, fd), free(line));
		}
		(free(line), close(fd));
	}
	return (wait_childs(call_cmds(&pipex, (char **)(av + 2 + pipex.here_doc))));
}
