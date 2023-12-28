/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:08:05 by abasdere          #+#    #+#             */
/*   Updated: 2023/12/27 00:08:20 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_controls(int *controls, int ac)
{
	controls[0] = 1;
	controls[1] = 0;
	controls[2] = ac - 1;
	controls[3] = 0;
}
