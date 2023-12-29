/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:08:02 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/28 23:47:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_and_free(t_pipex *pipex)
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
	close(pipex->infile);
	close(pipex->outfile);
	return (1);
}
