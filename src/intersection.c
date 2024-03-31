/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:55:59 by flafi             #+#    #+#             */
/*   Updated: 2024/03/31 21:56:34 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

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

void	move_to_next_intersection(float *v_x, float *v_y, float *x_step,
		float *y_step, t_game *game, int pixel)
{
	while (wall_hit(*v_x - pixel, *v_y, game))
	{
		*v_x += *x_step;
		*v_y += *y_step;
	}
}
float	get_h_inter(t_game *game, float angl)
{
	int		pixel;
	float	delta_x;
	float	delta_y;

	float h_x, h_y, x_step, y_step;
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(game->ply.plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = game->ply.plyr_x + (h_y - game->ply.plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y')
			&& x_step < 0))
		x_step *= -1;
	while (1)
	{
		if (!wall_hit(h_x, h_y - pixel, game))
			break ;
		h_x += x_step;
		h_y += y_step;
	}
	delta_x = h_x - game->ply.plyr_x;
	delta_y = h_y - game->ply.plyr_y;
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

float	get_v_inter(t_game *game, float angl)
{
	float	vt_x;
	float	vt_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	vt_x = floor(game->ply.plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &vt_x, &x_step, 0);
	vt_y = game->ply.plyr_y + (vt_x - game->ply.plyr_x) * tan(angl);
	adjust_y_step(&y_step, angl);
	move_to_next_intersection(&vt_x, &vt_y, &x_step, &y_step, game, pixel);
	game->ray.vert_x = vt_x;
	game->ray.vert_y = vt_y;
	return (calculate_distance(vt_x, vt_y, game->ply.plyr_x, game->ply.plyr_y));
}
