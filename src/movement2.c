/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:42:25 by flafi             #+#    #+#             */
/*   Updated: 2024/03/31 21:42:25 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

// Adjust angle to keep it within [0, 2π)
void	adjust_angle(double *angle)
{
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
	while (*angle < 0)
		*angle += 2 * M_PI;
}

// checks for wall collisions
int	is_valid_move(const t_game *game, int new_x, int new_y)
{
	int		map_grid_x;
	int		map_grid_y;
	double	inv_tile_size;

	inv_tile_size = 1.0 / TILE_SIZE;
	map_grid_x = (int)(new_x * inv_tile_size);
	map_grid_y = (int)(new_y * inv_tile_size);
	return (game->map.grid[map_grid_y][map_grid_x] != '1'
		&& game->map.grid[(int)(new_y * inv_tile_size)][(int)(new_x
			* inv_tile_size)] != '1');
}

// move the player and checks for wall collisions
void	move_player(t_game *game, double move_x, double move_y)
{
	int	new_x;
	int	new_y;

	new_x = round(game->ply.plyr_x + move_x);
	new_y = round(game->ply.plyr_y + move_y);
	if (is_valid_move(game, new_x, new_y))
	{
		game->ply.plyr_x = new_x;
		game->ply.plyr_y = new_y;
	}
}

// Main function to hook the player
void	hook(t_game *game, double move_x, double move_y)
{
	move_x = 0;
	move_y = 0;
	if (game->ply.rot == 1)
		rotate_player(game, 1);
	else if (game->ply.rot == -1)
		rotate_player(game, 0);
	if (game->ply.l_r == 1)
		move_right(game, &move_x, &move_y);
	else if (game->ply.l_r == -1)
		move_left(game, &move_x, &move_y);
	if (game->ply.u_d == 1)
		move_up(game, &move_x, &move_y);
	else if (game->ply.u_d == -1)
		move_down(game, &move_x, &move_y);
	move_player(game, move_x, move_y);
}
