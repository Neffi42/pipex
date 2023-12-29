/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:34:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 03:18:27 by abasdere         ###   ########.fr       */
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
	size_t	i;

	i = -1;
	if (!pname || !message)
		return ;
	ft_dprintf(STDERR_FILENO, "%s: ", pname);
	while (message[++i])
		ft_putchar_fd(ft_tolower(message[i]), STDERR_FILENO);
	if (el)
		ft_dprintf(STDERR_FILENO, ": %s\n", el);
	else
		ft_putstr_fd(":\n", STDERR_FILENO);
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
