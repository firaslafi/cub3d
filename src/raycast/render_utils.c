/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:51:12 by flafi             #+#    #+#             */
/*   Updated: 2024/04/10 09:52:59 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycast.h"

void	ref_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0)
		x = 0;
	else if (x >= S_W)
		x = S_W - 1;
	if (y < 0)
		y = 0;
	else if (y >= S_H)
		y = S_H - 1;
	mlx_put_pixel(game->scn.img, x, y, color);
}

int	rgb_to_rgba(int r, int g, int b, int a)
{
	int	rgba;

	rgba = 0;
	rgba |= (r & 0xFF) << 24;
	rgba |= (g & 0xFF) << 16;
	rgba |= (b & 0xFF) << 8;
	rgba |= (a & 0xFF);
	return (rgba);
}

// draw the floor and the ceiling
// ceiling is the 1st param
void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)
{
	int	i;

	i = b_pix;
	while (i < S_H)
		ref_mlx_pixel_put(game, ray, i++,
			rgb_to_rgba(game->parser.map->floor_color[0],
				game->parser.map->floor_color[1],
				game->parser.map->floor_color[2], 255));
	i = 0;
	while (i < t_pix)
		ref_mlx_pixel_put(game, ray, i++,
			rgb_to_rgba(game->parser.map->ceiling_color[0],
				game->parser.map->ceiling_color[1],
				game->parser.map->ceiling_color[2], 255));
}
