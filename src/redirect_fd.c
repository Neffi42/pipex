/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:40:44 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 18:26:42 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_fd(int *newfd, int i, int len, int oldfd)
{
	int	fd;

	fd = dup2(newfd[i], oldfd);
	if (fd == -1 && close_nfd(newfd, len))
		error_errno(NULL, 0);
	return (fd);
}
