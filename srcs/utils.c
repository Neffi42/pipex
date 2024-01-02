/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:45:08 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 14:35:57 by abasdere         ###   ########.fr       */
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
		(free_all(pipex), exit(error(EXIT_FAILURE, PNAME, ERROR_NO_PATH)));
	path = ft_substr(pipex->envp[i], 5, ft_strlen(pipex->envp[i]) - 5);
	if (!path)
		(perror(PNAME), free_all(pipex), exit(errno));
	pipex->path = ft_split(path, ':');
	free(path);
	if (!pipex->path)
		(perror(PNAME), free_all(pipex), exit(errno));
}

static void	init_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->pipes = ft_calloc(pipex->nb_pipes + 1, sizeof(int *));
	if (!pipex->pipes)
		(perror(PNAME), free_all(pipex), exit(errno));
	pipex->pipes[pipex->nb_pipes] = NULL;
	while (++i < pipex->nb_pipes)
	{
		pipex->pipes[i] = ft_calloc(3, sizeof(int));
		if (!pipex->pipes[i] || pipe(pipex->pipes[i]) == -1)
			(perror(PNAME), free_all(pipex), exit(errno));
	}
}

void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp)
{
	pipex->envp = envp;
	pipex->nb_pipes = ac - 4;
	pipex->cmd = NULL;
	pipex->here_doc = 0;
	pipex->path = NULL;
	pipex->pipes = NULL;
	if (!ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)))
		pipex->here_doc = 1;
	pipex->limiter = (char *)av[2];
	pipex->infile = STDIN_FILENO;
	if (!pipex->here_doc)
		pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
		(perror(PNAME), free_all(pipex), exit(errno));
	pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		(perror(PNAME), free_all(pipex), exit(errno));
	(find_path(pipex), init_pipes(pipex));
}

void	free_all(t_pipex *pipex)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (pipex->pipes && pipex->pipes[++i])
	{
		j = -1;
		while (pipex->pipes[i][++j])
			close(pipex->pipes[i][j]);
		free(pipex->pipes[i]);
	}
	if (pipex->pipes)
		free(pipex->pipes);
	if (pipex->path)
		ft_free_tab(pipex->path);
	(close(pipex->infile), close(pipex->outfile));
}


int	error(int code, char *name, char *message)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", name, message);
	return (code);
}
