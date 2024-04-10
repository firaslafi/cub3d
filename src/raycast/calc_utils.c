/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:51:17 by flafi             #+#    #+#             */
/*   Updated: 2024/04/10 09:51:16 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/cub_3d.h"
#include "../include/raycast.h"


// calculate X of the texture based on the player's position and wall distance
double	get_x_pos(mlx_texture_t *texture, t_game *game, double wall_distance)
{
	double	x_o;
	double	cosi;
	double	sini;
	double	w_totile;

	cosi = cos(game->ray.ray_ngl);
	sini = sin(game->ray.ray_ngl);
	w_totile = (texture->width / TILE_SIZE);
	if (game->ray.flag == 1)
		x_o = fmod((game->ply.plyr_x + wall_distance * cosi) * w_totile,
				texture->width);
	else
		x_o = fmod((game->ply.plyr_y + wall_distance * sini) * w_totile,
				texture->width);
	return (x_o);
}

// reverse bytes to get real colors
uint32_t	rev_byte(uint32_t c)
{
	return (((c & 0x000000FF) << 24) | ((c & 0x0000FF00) << 8)
		| ((c & 0x00FF0000) >> 8) | ((c & 0xFF000000) >> 24));
}

// ray casting section *****
// check the unit circle
int	unit_circle(float angle, char c)
{
	int	result;

	result = 0;
	if (c == 'x' && angle > 0 && angle < M_PI)
	{
		result = 1;
	}
	else if (c == 'y' && angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
	{
		result = 1;
	}
	return (result);
}

// check the intersection horizon
int	intersek_chck(float angle, float *inter, float *step, int horizn)
{
	int	in_range;

	in_range = (horizn && angle > 0 && angle < M_PI) || (!horizn
			&& !(angle > M_PI / 2 && angle < 3 * M_PI / 2));
	if (in_range)
	{
		*inter += TILE_SIZE;
		return (-1);
	}
	*step *= -1;
	return (1);
}

/*to check the wall hit we need ti get the x,y pos in the map
and do the raycasting maths*/
int	wall_hit(float x, float y, t_game *game)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if (x_m >= (int)game->map.max_width || y_m >= (int)game->map.map_height)
		return (0);
	return (game->map.grid[y_m][x_m] != '1');
}
