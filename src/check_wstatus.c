/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wstatus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:00:26 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/26 19:00:44 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_wstatus(int wstatus, int **fd)
{
	int	status_code;

	if (!WIFEXITED(wstatus))
		error_status(3, ERROR_WSTATUS, fd, 1);
	status_code = WEXITSTATUS(wstatus);
	if (status_code && close_and_free(fd, 1))
		exit(status_code);
}
