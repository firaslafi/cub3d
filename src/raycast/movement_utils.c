/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:51:20 by flafi             #+#    #+#             */
/*   Updated: 2024/03/31 14:51:20 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

// Helper function to calculate movement to the right
void	move_right(t_game *game, double *move_x, double *move_y)
{
	*move_x += -sin(game->ply.angle) * PLAYER_SPEED;
	*move_y += cos(game->ply.angle) * PLAYER_SPEED;
}

// Helper function to calculate movement to the left
void	move_left(t_game *game, double *move_x, double *move_y)
{
	*move_x += sin(game->ply.angle) * PLAYER_SPEED;
	*move_y += -cos(game->ply.angle) * PLAYER_SPEED;
}

// Helper function to calculate movement upwards
void	move_up(t_game *game, double *move_x, double *move_y)
{
	*move_x += cos(game->ply.angle) * PLAYER_SPEED;
	*move_y += sin(game->ply.angle) * PLAYER_SPEED;
}

// Helper function to calculate movement downwards
void	move_down(t_game *game, double *move_x, double *move_y)
{
	*move_x += -cos(game->ply.angle) * PLAYER_SPEED;
	*move_y += -sin(game->ply.angle) * PLAYER_SPEED;
}
