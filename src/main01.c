/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:26:27 by flafi             #+#    #+#             */
/*   Updated: 2024/03/31 14:26:27 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

//############################## THE WALL RENDERING CODE ##############################//

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


// draw the floor and the ceiling
void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)
{
	int i;

	i = b_pix;
	while (i < S_H)
		ref_mlx_pixel_put(game, ray, i++, 0x005C4033);
	i = 0;
	while (i < t_pix)
		ref_mlx_pixel_put(game, ray, i++, 0xB99470FF);
}


// calculate X of the texture based on the player's position and wall distance
double	get_x_pos(mlx_texture_t *texture, t_game *game, double wall_distance)
{
	double	x_o;

	if (game->ray.flag == 1)
		x_o = fmod((game->ply.plyr_x + wall_distance * cos(game->ray.ray_ngl))
			* (texture->width / TILE_SIZE), texture->width);
	else
		x_o = fmod((game->ply.plyr_y + wall_distance * sin(game->ray.ray_ngl))
			* (texture->width / TILE_SIZE), texture->width);
	return (x_o);
}
// reverse bytes to get real colors
uint32_t	rev_byte(uint32_t c)
{
	return ((c & 0x000000FF) << 24) | ((c & 0x0000FF00) << 8) | ((c & 0x00FF0000) >> 8) | ((c & 0xFF000000) >> 24);
}




// ray casting section *****
// check the unit circle
int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

// check the intersection
int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
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
	if (y_m < 0 || y_m >= (int)game->map.map_height || x_m < 0
		|| x_m >= (int)game->map.max_width)
		return (0);
	if (game->map.grid[y_m][x_m] == '1')
		return (0);
	return (1);
}

/* run the game loop, create new imgs,
	cast the rays put the image to the window*/
void	game_loop(void *param)
{
	t_game	*game;

	game = param;
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

int	main(int ac, char **av) // main function
{
	t_game game;

	if (checking_map(ac, av, &game))
		return (EXIT_FAILURE);
	print_map_details(&game);
	start_the_game(&game); // start the game
	return (close_game(&game), EXIT_SUCCESS);
}
