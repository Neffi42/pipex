/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 22:18:11 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:46:02 by abasdere         ###   ########.fr       */
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
		error_status(pipex, CODE_NO_PATH, NULL);
	path = ft_substr(pipex->envp[i], 5, ft_strlen(pipex->envp[i]) - 5);
	if (!path)
		error_status(pipex, CODE_MALLOC, "ft_substr");
	pipex->path = ft_split(path, ':');
	free(path);
}

static void	init_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->pipes = calloc(pipex->nb_pipes + 1, sizeof(int *));
	if (!pipex->pipes)
		error_status(pipex, CODE_MALLOC, "init_pipes");
	while (++i < pipex->nb_pipes)
	{
		pipex->pipes[i] = ft_calloc(3, sizeof(int));
		if (!pipex->pipes[i])
			error_status(pipex, CODE_MALLOC, "init_pipes");
		if (pipe(pipex->pipes[i]) == -1)
			error_errno(pipex, errno, "pipe");
	}
}

void	init_files(t_pipex *pipex, char *infile, char *outfile)
{
	if (pipex->infile != STDIN_FILENO)
	{
		pipex->infile = open(infile, O_RDONLY);
		if (pipex->infile == -1)
			error_errno(pipex, errno, infile);
	}
	pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		error_errno(pipex, errno, outfile);
	find_path(pipex);
	if (!pipex->path)
		error_status(pipex, CODE_MALLOC, "find_path");
	if (pipex->nb_pipes > 0)
		init_pipes(pipex);
}
