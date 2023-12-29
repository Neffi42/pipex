/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:35:54 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:41:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pipes(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
}

void	call_cat(t_pipex *pipex)
{
	int		wstatus;
	pid_t	pid;

	pipex->cmd = "cat";
	pid = fork();
	if (pid == -1)
		error_errno(pipex, errno, NULL);
	if (!pid)
	{
		if (!pipex->here_doc)
			redirect_fd(pipex, pipex->infile, STDIN_FILENO);
		redirect_fd(pipex, pipex->outfile, STDOUT_FILENO);
		close_pipes(pipex);
		call_cmd(pipex);
	}
	close_pipes(pipex);
	wait(&(wstatus));
	check_wstatus(pipex, wstatus);
}
