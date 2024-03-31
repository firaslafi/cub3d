/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:25:47 by flafi             #+#    #+#             */
/*   Updated: 2024/03/31 14:25:47 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

// release key but for directions
void	release_movement_keys(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->ply.l_r = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->ply.l_r = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->ply.u_d = 0;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->ply.u_d = 0;
}

// release key but for rotation
void	release_rotation_keys(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->ply.rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->ply.rot = 0;
}

// release keys
void	ft_release_key(mlx_key_data_t keydata, t_game *game)
{
	release_movement_keys(game, keydata);
	release_rotation_keys(game, keydata);
}

// mlx key press register and release
void	mlx_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		finish(game, "finish game", MSG);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game->ply.l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game->ply.l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		game->ply.u_d = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->ply.u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->ply.rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->ply.rot = 1;
	ft_release_key(keydata, game);
}

// rotate the player
void	rotate_player(t_game *game, int i)
{
	double	rotation;

	if (i == 1)
	{
		rotation = ROTATION_SPEED;
	}
	else
	{
		rotation = -ROTATION_SPEED;
	}
	game->ply.angle += rotation;
	adjust_angle(&(game->ply.angle));
}
