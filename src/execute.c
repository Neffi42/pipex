/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:39:46 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 18:48:56 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(const char *cmd, char **envp, int **fd)
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
