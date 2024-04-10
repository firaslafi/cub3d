/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:51:25 by flafi             #+#    #+#             */
/*   Updated: 2024/04/10 06:46:00 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycast.h"

// get the vertical intersection
float	calculate_distance(float v_x, float v_y, float plyr_x, float plyr_y)
{
	return (sqrt(pow(v_x - plyr_x, 2) + pow(v_y - plyr_y, 2)));
}

void	adjust_y_step(float *y_step, float angl)
{
	if ((unit_circle(angl, 'x') && *y_step < 0) || (!unit_circle(angl, 'x')
			&& *y_step > 0))
		*y_step *= -1;
}

float	get_h_inter(t_game *game, float angl)
{
	t_vars	vars;

	vars.y_step = TILE_SIZE;
	vars.x_step = TILE_SIZE / tan(angl);
	vars.vt_y = floor(game->ply.plyr_y / TILE_SIZE) * TILE_SIZE;
	vars.pixel = intersek_chck(angl, &vars.vt_y, &vars.y_step, 1);
	vars.vt_x = game->ply.plyr_x + (vars.vt_y - game->ply.plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && vars.x_step > 0) || (!unit_circle(angl, 'y')
			&& vars.x_step < 0))
		vars.x_step *= -1;
	while (wall_hit(vars.vt_x, vars.vt_y - vars.pixel, game))
	{
		vars.vt_x += vars.x_step;
		vars.vt_y += vars.y_step;
	}
	return (sqrt(pow(vars.vt_x - game->ply.plyr_x, 2) + pow(vars.vt_y
				- game->ply.plyr_y, 2)));
}

void	move_to_next_intersection(t_intersection *inter, t_game *game)
{
	while (wall_hit(*(inter->v_x) - inter->pixel, *(inter->v_y), game))
	{
		*(inter->v_x) += *(inter->x_step);
		*(inter->v_y) += *(inter->y_step);
	}
}

float	get_v_inter(t_game *game, float angl)
{
	t_vars			vars;
	t_intersection	inter;

	vars.x_step = TILE_SIZE;
	vars.y_step = TILE_SIZE * tan(angl);
	vars.vt_x = floor(game->ply.plyr_x / TILE_SIZE) * TILE_SIZE;
	vars.pixel = intersek_chck(angl, &vars.vt_x, &vars.x_step, 0);
	vars.vt_y = game->ply.plyr_y + (vars.vt_x - game->ply.plyr_x) * tan(angl);
	adjust_y_step(&vars.y_step, angl);
	inter = init_intersection(&vars);
	move_to_next_intersection(&inter, game);
	game->ray.vert_x = vars.vt_x;
	game->ray.vert_y = vars.vt_y;
	return (calculate_distance(vars.vt_x, vars.vt_y, game->ply.plyr_x,
			game->ply.plyr_y));
}
