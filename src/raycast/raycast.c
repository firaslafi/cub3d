/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:51:03 by flafi             #+#    #+#             */
/*   Updated: 2024/04/10 06:33:28 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycast.h"

// cast the rays
/* ray angle gets the starting angel and then we loop through the rays
we initialize the wall flag to 0, (no wall until we really find a wall)
get both horizontal and vertical intersection then we check the distance
between the intersection and we get the distance if v <= h we set V as
distance else it is H and we flag for a wall we loop through all the
rays and angels updating them of course
*/
void	cast_rays(t_game *game)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	game->ray.ray_ngl = game->ply.angle - (game->ply.fov_rd / 2);
	while (ray < S_W)
	{
		game->ray.flag = 0;
		h_inter = get_h_inter(game, nor_angle(game->ray.ray_ngl));
		v_inter = get_v_inter(game, nor_angle(game->ray.ray_ngl));
		if (v_inter <= h_inter)
			game->ray.distance = v_inter;
		else
		{
			game->ray.distance = h_inter;
			game->ray.flag = 1;
		}
		render_wall(game, ray);
		ray++;
		game->ray.ray_ngl += (game->ply.fov_rd / S_W);
	}
}

/* run the game loop, create new imgs,
	cast the rays put the image to the window*/
void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_delete_image(game->mlx, game->scn.img);
	game->scn.img = mlx_new_image(game->mlx, S_W, S_H);
	hook(game, 0, 0);
	cast_rays(game);
	mlx_image_to_window(game->mlx, game->scn.img, 0, 0);
}

// initializing and setting the player in the center of the tile X,Y
void	init_the_player(t_game *game)
{
	game->ply.plyr_x = game->ply.pos.x * TILE_SIZE + TILE_SIZE / 2;
	game->ply.plyr_y = game->ply.pos.y * TILE_SIZE + TILE_SIZE / 2;
	game->ply.fov_rd = (FOV * M_PI) / 180;
	// game->ply.angle = M_PI;
	game->ply.angle = take_ply_angel(game);
}

// start the raycast, init player, run game loop and key hook
void	raycasting_rendering(t_game *game)
{
	init_the_player(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, &mlx_key, game);
	mlx_loop(game->mlx);
}
