/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:38:21 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/27 00:52:31 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	copy_file(const char *path1, const char *path2)
{
	int		file1;
	int		file2;
	char	*line;

	file1 = open(path1, O_RDONLY);
	if (file1 == -1)
		error_errno(NULL, 0);
	file2 = open(path2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1 && !close(file1))
		error_errno(NULL, 0);
	line = ft_get_next_line(file1);
	while (line)
	{
		write(file2, line, ft_strlen(line));
		free(line);
		line = ft_get_next_line(file1);
	}
	close(file1);
	close(file2);
	exit (0);
}
