/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:39:46 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/27 00:04:34 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execute(const char *cmd, char **envp, int **fd)
{
	char	**tab;
	int		status;

	tab = ft_split(cmd, ' ');
	if (!tab)
		error_status(2, ERROR_MALLOC, fd, 1);
	tab[0] = ft_freejoin("/usr/bin/", tab[0], 1);
	if (!tab[0] && !ft_free_tab(tab))
		error_status(2, ERROR_MALLOC, fd, 1);
	status = execve(tab[0], tab, envp);
	ft_free_tab(tab);
	return (status);
}

void	exec_child(const char *cmd, char **envp, int **fd, int *controls)
{
	size_t	i;

	i = -1;
	redirect_fd(fd[controls[1]][0], STDIN_FILENO, fd);
	if (controls[0] + 1 == controls[2])
		redirect_fd(fd[0][1], STDOUT_FILENO, fd);
	else
		redirect_fd(fd[controls[1] + 1][1], STDOUT_FILENO, fd);
	while (fd[++i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	execute(cmd, envp, fd);
}
