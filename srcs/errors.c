/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:34:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 02:45:15 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_message(int code)
{
	if (code == CODE_USAGE)
		return (ERROR_USAGE);
	else if (code == CODE_MALLOC)
		return (ERROR_MALLOC);
	else if (code == CODE_NO_PATH)
		return (ERROR_NO_PATH);
	else if (code == CODE_WSTATUS)
		return (ERROR_WSTATUS);
	else if (code == CODE_PERM)
		return (ERROR_PERM);
	return (NULL);
}

void	print_error(char *pname, char *message, char *el)
{
	if (!pname || !message)
		return ;
	if (el)
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", pname, message, el);
	else
		ft_dprintf(STDERR_FILENO, "%s: %s:\n", pname, message);
}

void	error_errno(t_pipex *pipex, int ernum, char *el)
{
	if (pipex)
	{
		print_error(pipex->pname, strerror(ernum), el);
		close_and_free(pipex);
	}
	exit(ernum);
}

void	error_status(t_pipex *pipex, int code, char *el)
{
	if (pipex && code > 0)
		print_error(pipex->pname, find_message(code), el);
	if (pipex)
		close_and_free(pipex);
	exit(code);
}
