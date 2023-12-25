/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:34:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/25 19:25:05 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_errno(void)
{
	perror(strerror(errno));
	exit(errno);
}

void	error_status(int status, char *message)
{
	ft_dprintf(STDERR_FILENO, "%s\n", message);
	exit(status);
}
