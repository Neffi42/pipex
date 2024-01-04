/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/04 19:15:08 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute(t_pipex *pipex, int index, pid_t *pid)
{
	int		fd[2];
	size_t	i;

	i = -1;
	if (!index)
		fd[0] = pipex->infile;
	else
		fd[0] = pipex->pipes[index - 1][0];
	if (index == pipex->nb_pipes)
		fd[1] = pipex->outfile;
	else
		fd[1] = pipex->pipes[index][1];
	*pid = fork();
	if (*pid == -1)
		(perror("fork"), free_all(pipex), exit(-1));
	if (!(*pid))
	{
		if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
			(perror("dup2"), free_all(pipex), exit(-1));
		while (pipex->pipes[++i])
			(close(pipex->pipes[i][0]), close(pipex->pipes[i][1]));
		(close(pipex->infile), close(pipex->outfile));
		execve(pipex->cmd[0], pipex->cmd, pipex->envp);
		(perror("execve"), free_all(pipex), exit(-1));
	}
}

static int	init_cmd(t_pipex *pipex)
{
	char	*name;
	char	*tmp;
	int		i;

	name = pipex->cmd[0];
	if (ft_strchr(name, '/') != NULL && access(name, F_OK | X_OK) != 0)
		return (127);
	else if (ft_strchr(name, '/') != NULL && access(name, F_OK | X_OK) == 0)
		return (0);
	i = -1;
	while (pipex->path && pipex->path[++i])
	{
		tmp = ft_freejoin(ft_strjoin(pipex->path[i], "/"), name, -1);
		if (!tmp)
			return (-1);
		if (!access(tmp, X_OK))
		{
			(free(pipex->cmd[0]), pipex->cmd[0] = tmp);
			return (0);
		}
		free(tmp);
	}
	return (127);
}

static pid_t	call_cmds(t_pipex *pipex, char **av)
{
	pid_t	pid;
	int		i;
	int		code;

	i = -1;
	while (++i <= pipex->nb_pipes && ++av)
	{
		(ft_free_tab(pipex->cmd), pipex->cmd = ft_split(*(av), ' '));
		if (!pipex->cmd || !pipex->cmd[0])
		{
			(ft_dprintf(2, "%s: %s", *av, ERR_CMD), pid = -1);
			continue ;
		}
		code = init_cmd(pipex);
		if (code == -1)
			(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(-1));
		else if (code == 127)
			(ft_dprintf(2, "%s: %s", pipex->cmd[0], ERR_CMD), pid = -1);
		else
			execute(pipex, i, &pid);
	}
	return (free_all(pipex), pid);
}

static int	wait_childs(pid_t pid)
{
	int	wstatus;
	int	code;

	code = EXIT_FAILURE;
	while (errno != ECHILD)
		if (wait(&wstatus) == pid && WIFEXITED(wstatus))
			code = WEXITSTATUS(wstatus);
	if (pid == -1)
		return (127);
	return (code);
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
	return (wait_childs(call_cmds(&pipex, (char **)(av + 1 + pipex.here_doc))));
}
