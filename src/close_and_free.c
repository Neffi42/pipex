/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:08:02 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 18:21:29 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_and_free(int **fd, int call_close)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (fd[++i])
	{
		j = -1;
		while (call_close && fd[i][++j])
			close(fd[i][j]);
		free(fd[i]);
	}
	free(fd);
	return (1);
}
