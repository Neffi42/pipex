/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:13:26 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/04 18:10:26 by abasdere         ###   ########.fr       */
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
	char	**cmd;
	int		here_doc;
	char	*limiter;
}	t_pipex;

void	free_all(t_pipex *pipex);
int		find_heredoc(t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp);

# define ERR_ARGS "usage: ./pipex <infile> <cmd_1> ... <cmd_n> <outfile>\n"
# define ERR_BONUS "usage: ./pipex here_doc <limiter> <cmd_1> ... <cmd_n> \
<outfile>\n"
# define ERR_CMD "command not found\n"
# define ERR_CMD2 "Command '' not found\n"
# define ERR_MEM "memory allocation error\n"
# define ERR_PATH "no $PATH found\n"
# define ERR_LIM  "limiter cannot be NULL\n"

#endif
