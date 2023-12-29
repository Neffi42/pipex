/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:39:46 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:44:45 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_pipex *pipex, int index, int end)
{
	size_t	i;

	i = -1;
	if (index == 2 && !pipex->here_doc)
		redirect_fd(pipex, pipex->infile, STDIN_FILENO);
	else if (!(index == 3 && pipex->here_doc))
		redirect_fd(pipex, pipex->pipes[pipex->pipe - 1][0], STDIN_FILENO);
	if (index + 1 == end)
		redirect_fd(pipex, pipex->outfile, STDOUT_FILENO);
	else
		redirect_fd(pipex, pipex->pipes[pipex->pipe][1], STDOUT_FILENO);
	while (pipex->pipes && pipex->pipes[++i])
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
	}
	call_cmd(pipex);
}
