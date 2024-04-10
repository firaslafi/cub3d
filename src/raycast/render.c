/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:00:53 by flafi             #+#    #+#             */
/*   Updated: 2024/04/10 09:51:34 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/cub_3d.h"
#include "../include/raycast.h"

/*to render the wall you need to get the top and bottom, position of the wall
on the screen do some crazy internet math that results in fish eye effect
that you need to fix with more internet math, then set the wall height
by gettunng top pixel and heigh maths and making sure the bottom is
on the ground the draw it includinh floor and ceiling according
to the input from the parsed .cub map*/
// fix fish eye effect
void	render_wall(t_game *game, int ray)
{
	double	wall_h;
	double	cos_val;
	double	tan_val;
	double	bot_pix;
	double	top_pix;

	cos_val = cos(nor_angle(game->ray.ray_ngl - game->ply.angle));
	tan_val = tan(game->ply.fov_rd / 2);
	game->ray.distance = adjust_distance(game->ray.distance, cos_val);
	wall_h = calculate_wall_height(game->ray.distance, tan_val);
	bot_pix = (S_H / 2) + (wall_h / 2);
	top_pix = (S_H / 2) - (wall_h / 2);
	if (bot_pix > S_H)
		bot_pix = S_H - 1;
	if (top_pix < 0)
		top_pix = 1;
	game->ray.index = ray;
	draw_wall(game, top_pix, bot_pix, wall_h);
	draw_floor_ceiling(game, ray, top_pix, bot_pix);
}

void	draw_wall(t_game *game, int top_pix, int bot_pix, double wall_h)
{
	double			x_pos;
	double			y_pos;
	mlx_texture_t	*texture;
	uint32_t		*array;
	double			factor;

	array = 0;
	texture = NULL;
	texture = get_textures(game, game->ray.flag);
	array = (uint32_t *)texture->pixels;
	x_pos = 0.0;
	x_pos = get_x_pos(texture, game, game->ray.distance);
	y_pos = 0.0;
	factor = 0;
	factor = (double)texture->height / wall_h;
	y_pos = factor * (top_pix - (S_H / 2) + (wall_h / 2));
	if (y_pos < 0)
		y_pos = 0;
	while (top_pix < bot_pix)
	{
		ref_mlx_pixel_put(game, game->ray.index, top_pix,
			rev_byte(array[(int)y_pos * texture->width + (int)x_pos]));
		y_pos = y_pos + factor;
		top_pix += 1;
	}
}

// to fix fish eye effect
double	adjust_distance(double distance, double cos_val)
{
	return (distance * cos_val);
}

// get the wall heigh obviously
double	calculate_wall_height(double distance, double tan_val)
{
	return ((TILE_SIZE / distance) * ((S_W / 2) / tan_val));
}

// Normalize angle using modulo operation
// Ensure the result is within [0, 2π)
float	nor_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
