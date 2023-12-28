/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:39:51 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/27 00:22:46 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_io(const char *infile, const char *outfile, int **fd)
{
	fd[0][0] = open(infile, O_RDONLY);
	if (fd[0][0] == -1)
		error_errno(fd, 0);
	fd[0][1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[0][1] == -1 && !close(fd[0][0]))
		error_errno(fd, 0);
}

int	**init_fd(int ac, const char **av)
{
	int	**fd;
	int	i;
	int	nb_cmd;

	i = -1;
	nb_cmd = ac - 3;
	fd = calloc(nb_cmd + 1, sizeof(int *));
	if (!fd)
		error_status(2, ERROR_MALLOC, NULL, 0);
	while (++i < nb_cmd)
	{
		fd[i] = ft_calloc(3, sizeof(int));
		if (!fd[i])
			error_status(2, ERROR_MALLOC, fd, 0);
	}
	redirect_io(av[1], av[ac - 1], fd);
	i = 0;
	while (++i < nb_cmd)
		if (pipe(fd[i]) == -1)
			error_errno(fd, 1);
	return (fd);
}
