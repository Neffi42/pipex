/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:13:26 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:49:13 by abasdere         ###   ########.fr       */
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
	char	*pname;
	int		infile;
	int		outfile;
	int		nb_pipes;
	int		pipe;
	int		**pipes;
	char	*cmd;
	int		here_doc;
	char	*limiter;
}	t_pipex;

void	call_cat(t_pipex *pipex);
void	call_cmd(t_pipex *pipex);
void	check_wstatus(t_pipex *pipex, int wstatus);
void	child_creation(t_pipex *pipex, int ac, const char **av);
int		close_and_free(t_pipex *pipex);
void	print_error(char *pname, char *message, char *el);
void	error_errno(t_pipex *pipex, int ernum, char *el);
void	error_status(t_pipex *pipex, int code, char *el);
void	execute(t_pipex *pipex, int index, int end);
void	init_files(t_pipex *pipex, char *infile, char *outfile);
void	init_pipex(t_pipex *pipex, int ac, const char **av, char **envp);
int		redirect_fd(t_pipex *pipex, int newfd, int oldfd);

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
