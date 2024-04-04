/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:51:30 by flafi             #+#    #+#             */
/*   Updated: 2024/04/02 01:51:32 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

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
