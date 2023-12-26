/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:13:26 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/27 00:11:29 by abasdere         ###   ########.fr       */
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

# define ERROR_USAGE "Usage: ./pipex <infile> <cmd_1> ... <cmd_n> <outfile>"
# define ERROR_MALLOC "Malloc failed"
# define ERROR_WSTATUS "Execution didn't terminated normally"

void	check_wstatus(int wstatus, int **fd);
int		close_and_free(int **fd, int call_close);
void	close_pipes(int **fd, int *controls);
void	error_errno(int **fd, int call_close);
void	error_status(int status, char *message, int **fd, int call_close);
void	exec_child(const char *cmd, char **envp, int **fd, int *controls);
void	init_controls(int *controls, int ac);
int		**init_fd(int ac, const char **av);
int		redirect_fd(int newfd, int oldfd, int **fd);

#endif
