/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:40:44 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 23:46:16 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_fd(int newfd, int oldfd, int **fd)
{
	int	fd2;

	fd2 = dup2(newfd, oldfd);
	if (fd2 == -1)
		error_errno(fd, 1);
	return (fd2);
}
