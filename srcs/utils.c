/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:45:08 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/04 19:01:25 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	find_path(t_pipex *pipex)
{
	size_t	i;
	char	*path;

	i = 0;
	while (pipex->envp[i] && !ft_strnstr(pipex->envp[i], "PATH", 4))
		i++;
	if (!pipex->envp[i])
		return ;
	path = ft_substr(pipex->envp[i], 5, ft_strlen(pipex->envp[i]) - 5);
	if (!path)
		(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(-1));
	pipex->path = ft_split(path, ':');
	free(path);
	if (!pipex->path)
		(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(-1));
}

static void	init_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->pipes = ft_calloc(pipex->nb_pipes + 1, sizeof(int *));
	if (!pipex->pipes)
		(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(-1));
	pipex->pipes[pipex->nb_pipes] = NULL;
	while (++i < pipex->nb_pipes)
	{
		pipex->pipes[i] = ft_calloc(3, sizeof(int));
		if (!pipex->pipes[i] || pipe(pipex->pipes[i]) == -1)
			(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(-1));
	}
}

void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp)
{
	pipex->envp = envp;
	pipex->nb_pipes = ac - 4 - pipex->here_doc;
	pipex->cmd = NULL;
	pipex->path = NULL;
	pipex->pipes = NULL;
	pipex->limiter = NULL;
	pipex->infile = 0;
	pipex->outfile = 0;
	if (pipex->here_doc)
	{
		pipex->limiter = ft_strjoin((char *)av[2], "\n");
		if (!pipex->limiter)
			(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(-1));
	}
	if (!pipex->here_doc)
		pipex->infile = open(av[1], O_RDONLY);
	if (pipex->here_doc)
		pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1 || pipex->outfile == -1)
		(perror("open"), free_all(pipex), exit(errno));
	(find_path(pipex), init_pipes(pipex));
}

void	free_all(t_pipex *pipex)
{
	size_t	i;

	i = -1;
	if (pipex->limiter)
		free(pipex->limiter);
	if (pipex->pipes)
	{
		while (pipex->pipes[++i])
			(close(pipex->pipes[i][0]), close(pipex->pipes[i][1]), \
			free(pipex->pipes[i]));
		free(pipex->pipes);
	}
	if (pipex->path)
		ft_free_tab(pipex->path);
	if (pipex->cmd)
		ft_free_tab(pipex->cmd);
	(close(pipex->infile), close(pipex->outfile));
}

int	find_heredoc(t_pipex *pipex)
{
	char	*file;
	int		fd;
	int		i;

	i = 2;
	file = ft_calloc(i, sizeof(char));
	if (!file)
		(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(-1));
	ft_memset(file, 'h', i - 1);
	while (!access(file, F_OK) && errno != ENOENT)
	{
		(free(file), file = ft_calloc(++i, sizeof(char)));
		if ((i < 0 || !file) && ft_dprintf(2, "%s", ERR_MEM))
			(free_all(pipex), exit(-1));
		ft_memset(file, 'h', i - 1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	pipex->infile = open(file, O_RDONLY);
	(unlink(file), free(file));
	if (pipex->infile == -1 || fd == -1)
		(perror("open"), close(fd), free_all(pipex), exit(errno));
	return (fd);
}
