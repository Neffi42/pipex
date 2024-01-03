/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:13:26 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/03 13:53:45 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_pipex
{
	char	**envp;
	char	**path;
	int		infile;
	int		outfile;
	int		nb_pipes;
	int		**pipes;
	char	*cmd;
	int		here_doc;
	char	*limiter;
}	t_pipex;

void	close_all(t_pipex *pipex);
void	free_all(t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp);

# define ERR_ARGS "usage: ./pipex <infile> <cmd_1> ... <cmd_n> <outfile>\n"
# define ERR_CMD "command not found\n"
# define ERR_CMD2 "Command '' not found\n"
# define ERR_MEM "memory allocation error\n"
# define ERR_PATH "no $PATH found\n"

#endif
