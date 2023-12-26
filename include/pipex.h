/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:13:26 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 15:16:01 by abasdere         ###   ########.fr       */
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

void	error_errno(void);
void	error_status(int status, char *message);
int		close_nfd(int *fd, size_t n);
int		execute(const char *cmd, char **envp);
int		redirect_fd(int *newfd, int i, int len, int oldfd);

#endif
