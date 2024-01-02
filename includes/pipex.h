/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:13:26 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/02 01:15:47 by abasdere         ###   ########.fr       */
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
	int		pipe;
	int		**pipes;
	char	*cmd;
	int		here_doc;
	char	*limiter;
}	t_pipex;

int		close_and_free(t_pipex *pipex);
void	execute(t_pipex *pipex, int index, int end);
void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp);
void	error(t_pipex *pipex, int code, char *el);
void	print_error(char *message, char *el);
int		wait_all(int start, int end);

# define PNAME "pipex"
# define HERE_DOC "here_doc"
# define ERROR_USAGE "usage: ./pipex <infile> <cmd_1> ... <cmd_n> <outfile>"
# define CODE_USAGE 1
# define ERROR_MALLOC "malloc failed"
# define CODE_MALLOC 2
# define ERROR_NO_PATH "no $PATH found"
# define CODE_NO_PATH 3
# define ERROR_WSTATUS "execution didn't terminated normally"
# define CODE_WSTATUS 4
# define ERROR_CMD "command not found"
# define CODE_CMD 5
# define ERROR_PERM "permission denied"
# define CODE_PERM 13

#endif
