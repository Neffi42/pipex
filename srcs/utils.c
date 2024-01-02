/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:45:08 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 01:24:13 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	find_path(t_pipex *pipex)
{
	size_t	i;
	char	*path;

	i = 0;
	while (pipex->envp[i] && !ft_strnstr(pipex->envp[i], "PATH", 4))
		i++;
	if (!pipex->envp[i])
		error(pipex, CODE_NO_PATH, NULL);
	path = ft_substr(pipex->envp[i], 5, ft_strlen(pipex->envp[i]) - 5);
	if (!path)
		return (perror(PNAME), (void)close_and_free(pipex), errno);
	pipex->path = ft_split(path, ':');
	free(path);
	if (!pipex->path)
		return (perror(PNAME), (void)close_and_free(pipex), errno);
	return (EXIT_SUCCESS);
}

static int	init_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->pipes = ft_calloc(pipex->nb_pipes + 1, sizeof(int *));
	if (!pipex->pipes)
		return (perror(PNAME), (void)close_and_free(pipex), errno);
	pipex->pipes[pipex->nb_pipes] = NULL;
	while (++i < pipex->nb_pipes)
	{
		pipex->pipes[i] = ft_calloc(3, sizeof(int));
		if (!pipex->pipes[i] || pipe(pipex->pipes[i]) == -1)
			return (perror(PNAME), (void)close_and_free(pipex), errno);
	}
	return (EXIT_SUCCESS);
}

void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp)
{
	int	x;

	pipex->envp = envp;
	pipex->nb_pipes = ac - 4;
	pipex->pipe = 0;
	pipex->cmd = NULL;
	pipex->here_doc = 0;
	if (!ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)))
		pipex->here_doc = 1;
	pipex->limiter = (char *)av[2];
	pipex->infile = STDIN_FILENO;
	if (!pipex->here_doc)
		pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1 && close_and_free(pipex))
		perror(PNAME);
	pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1 && close_and_free(pipex))
		perror(PNAME);
	x = find_path(pipex);
	if (!x)
		exit(x);
	x = init_pipes(pipex);
	if (!x)
		exit(x);
}

int	close_and_free(t_pipex *pipex)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (pipex->pipes && pipex->pipes[++i])
	{
		j = -1;
		while (pipex->pipes[i][++j] > 0)
			close(pipex->pipes[i][j]);
		free(pipex->pipes[i]);
	}
	if (pipex->pipes)
		free(pipex->pipes);
	if (pipex->path)
		ft_free_tab(pipex->path);
	if (pipex->infile > 0)
		close(pipex->infile);
	if (pipex->outfile > 0)
		close(pipex->outfile);
	return (EXIT_SUCCESS);
}
