/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:13:26 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 14:41:10 by abasdere         ###   ########.fr       */
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

void	free_all(t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp);
int		error(int code, char *name, char *message);

# define PNAME "pipex"
# define HERE_DOC "here_doc"
# define ERROR_USAGE "usage: ./pipex <infile> <cmd_1> ... <cmd_n> <outfile>"
# define ERROR_MALLOC "malloc failed"
# define ERROR_NO_PATH "no $PATH found"
# define ERROR_WSTATUS "execution didn't terminated normally"
# define ERROR_CMD "command not found"
# define CODE_CMD 127

#endif
