/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wstatus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:42:45 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:43:01 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_wstatus(t_pipex *pipex, int wstatus)
{
	int	status_code;

	if (!WIFEXITED(wstatus) && ft_dprintf(2, "TSET\n"))
		error_errno(pipex, wstatus, NULL);
	status_code = WEXITSTATUS(wstatus);
	if (status_code && close_and_free(pipex))
		exit(status_code);
}
