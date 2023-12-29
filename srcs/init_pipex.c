/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:45:35 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:45:52 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp)
{
	pipex->envp = envp;
	pipex->path = NULL;
	pipex->pname = (char *)av[0] + 2;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->nb_pipes = ac - 4;
	pipex->pipe = 0;
	pipex->pipes = NULL;
	pipex->cmd = NULL;
	pipex->here_doc = 0;
	pipex->limiter = NULL;
	if (ac > 3 && !ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)))
	{
		pipex->here_doc = 1;
		pipex->limiter = (char *)av[2];
	}
}
