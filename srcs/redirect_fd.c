/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:44:08 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:44:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_fd(t_pipex *pipex, int newfd, int oldfd)
{
	int	fd2;

	fd2 = dup2(newfd, oldfd);
	if (fd2 == -1)
		error_errno(pipex, errno, "redirect_fd");
	return (fd2);
}
