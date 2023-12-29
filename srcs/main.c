/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:10:58 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/29 04:46:48 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, const char **av, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex, ac, av, envp);
	if (ac < 3)
		error_status(&pipex, CODE_USAGE, NULL);
	if (pipex.here_doc)
		pipex.infile = STDIN_FILENO;
	init_files(&pipex, (char *)av[1], (char *)av[ac - 1]);
	if (ac == 3 + pipex.here_doc)
		call_cat(&pipex);
	else
		child_creation(&pipex, ac, av);
	close_and_free(&pipex);
	exit(EXIT_SUCCESS);
}
