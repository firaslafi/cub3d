/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:40:49 by flafi             #+#    #+#             */
/*   Updated: 2024/03/31 14:40:49 by flafi            ###   ########.fr       */
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
int is_valid_move(const t_game *game, int new_x, int new_y)
{
    int map_grid_x = (int)(new_x * inv_TILE_SIZE);
    int map_grid_y = (int)(new_y * inv_TILE_SIZE);
    
    return (game->map.grid[map_grid_y][map_grid_x] != '1'
        && game->map.grid[(int)(new_y * inv_TILE_SIZE)][(int)(new_x * inv_TILE_SIZE)] != '1');
}

// move the player and checks for wall collisions
void move_player(t_game *game, double move_x, double move_y)
{
    int new_x = round(game->ply.plyr_x + move_x);
    int new_y = round(game->ply.plyr_y + move_y);
    
    if (is_valid_move(game, new_x, new_y)) {
        game->ply.plyr_x = new_x;
        game->ply.plyr_y = new_y;
    }
}

// Main function to hook the player
void	hook(t_game *game, double move_x, double move_y)
{
	move_x = 0; // Reset movement variables
	move_y = 0;
	if (game->ply.rot == 1) // rotate right
		rotate_player(game, 1);
	else if (game->ply.rot == -1) // rotate left
		rotate_player(game, 0);
	if (game->ply.l_r == 1) // move right
		move_right(game, &move_x, &move_y);
	else if (game->ply.l_r == -1) // move left
		move_left(game, &move_x, &move_y);
	if (game->ply.u_d == 1) // move up
		move_up(game, &move_x, &move_y);
	else if (game->ply.u_d == -1) // move down
		move_down(game, &move_x, &move_y);
	move_player(game, move_x, move_y); // move the player
}
