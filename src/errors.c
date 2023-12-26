/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:34:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 12:39:57 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_errno(void)
{
	ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	exit(errno);
}

void	error_status(int status, char *message)
{
	if (message)
		ft_dprintf(STDERR_FILENO, "%s\n", message);
	exit(status);
}
