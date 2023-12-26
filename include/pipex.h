/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:13:26 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 19:00:55 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

# define ERROR_USAGE "Usage: ./pipex <infile> <cmd_1> ... <cmd_n> <outfile>"
# define ERROR_MALLOC "Malloc failed"
# define ERROR_WSTATUS "Execution didn't terminated normally"

void	error_errno(int **fd, int call_close);
void	error_status(int status, char *message, int **fd, int call_close);
int		close_and_free(int **fd, int call_close);
int		close_nfd(int *fd, size_t n);
int		**init_fd(int ac, const char **av);
int		execute(const char *cmd, char **envp, int **fd);
int		redirect_fd(int *newfd, int i, int len, int oldfd);
void	check_wstatus(int wstatus, int **fd);

#endif
