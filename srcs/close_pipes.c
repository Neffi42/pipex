/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:09:43 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/27 00:11:17 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int **fd, int *controls)
{
	if (!controls[1])
		close(fd[controls[1]++][0]);
	else
	{
		close(fd[controls[1]][0]);
		close(fd[controls[1]++][1]);
	}
	if (controls[0] + 1 == controls[2])
		close(fd[0][1]);
}
