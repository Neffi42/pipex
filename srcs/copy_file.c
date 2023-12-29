/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:38:21 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/28 22:45:06 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	copy_file(t_pipex *pipex)
{
	char	*line;

	line = ft_get_next_line(pipex->infile);
	while (line)
	{
		write(pipex->outfile, line, ft_strlen(line));
		free(line);
		line = ft_get_next_line(pipex->infile);
	}
	close_and_free(pipex);
	exit (EXIT_SUCCESS);
}
