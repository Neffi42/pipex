/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:34:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 18:22:18 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_errno(int **fd, int call_close)
{
	if (fd)
		close_and_free(fd, call_close);
	ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	exit(errno);
}

void	error_status(int status, char *message, int **fd, int call_close)
{
	if (fd)
		close_and_free(fd, call_close);
	if (message)
		ft_dprintf(STDERR_FILENO, "%s\n", message);
	exit(status);
}
