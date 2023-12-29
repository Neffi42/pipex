/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:43:38 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:44:50 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*init_cmd(char *path, char *cmd_name)
{
	char	*cmd;

	cmd = ft_strjoin(path, "/");
	if (!cmd)
		return (NULL);
	cmd = ft_freejoin(cmd, cmd_name, -1);
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	call_cmd(t_pipex *pipex)
{
	size_t	i;
	char	**tab;
	char	*cmd;

	i = -1;
	tab = ft_split(pipex->cmd, ' ');
	if (!tab)
		error_status(pipex, CODE_MALLOC, "ft_split");
	while (pipex->path[++(i)])
	{
		cmd = init_cmd(pipex->path[i], tab[0]);
		if (!cmd && !ft_free_tab(tab))
			error_status(pipex, CODE_MALLOC, "init_cmd");
		if (!access(cmd, X_OK))
			execve(cmd, tab, pipex->envp);
		free(cmd);
	}
	print_error(pipex->pname, ERROR_CMD, tab[0]);
	ft_free_tab(tab);
	exit(close_and_free(pipex));
}
