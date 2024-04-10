/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:51:30 by flafi             #+#    #+#             */
/*   Updated: 2024/04/10 06:33:55 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/cub_3d.h"
#include "../include/raycast.h"

t_intersection	init_intersection(t_vars *vars)
{
	t_intersection	inter;

	inter.v_x = &vars->vt_x;
	inter.v_y = &vars->vt_y;
	inter.x_step = &vars->x_step;
	inter.y_step = &vars->y_step;
	inter.pixel = vars->pixel;
	return (inter);
}
