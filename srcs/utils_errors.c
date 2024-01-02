/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:34:58 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 01:17:57 by abasdere         ###   ########.fr       */
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

void	print_error(char *message, char *el)
{
	size_t	i;

	i = -1;
	if (!message)
		return ;
	while (message[++i])
		message[i] = ft_tolower(message[i]);
	if (el)
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", PNAME, message, el);
	else
		ft_dprintf(STDERR_FILENO, "%s: %s:\n", PNAME, message);
}

void	error(t_pipex *pipex, int code, char *el)
{
	if (code > 0)
		print_error(find_message(code), el);
	if (pipex)
		close_and_free(pipex);
	exit(code);
}

int	wait_all(int start, int end)
{
	while (start++ < end)
		wait(NULL);
	return (EXIT_FAILURE);
}
