/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:50:37 by flafi             #+#    #+#             */
/*   Updated: 2024/04/02 01:50:37 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

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
	game->ply.angle = M_PI;
}

// start the game, init player, run game loop and key hook
void	start_the_game(t_game *game)
{
	game->mlx = mlx_init(S_W, S_H, "Cub3D", 0);
	init_the_player(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, &mlx_key, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (checking_map(ac, av, &game))
		return (EXIT_FAILURE);
	start_the_game(&game);
	return (close_game(&game), EXIT_SUCCESS);
}
