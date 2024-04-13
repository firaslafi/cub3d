/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_fucns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:02:04 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/04/13 02:16:19 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void print_map_details(t_game *game)
{
	if (game->map.no_xpm)
		printf(RED"NO:"RESET"%s\n", game->map.no_xpm);
	if (game->map.so_xpm)
		printf(RED"SO:"RESET"%s\n", game->map.so_xpm);
	if (game->map.ea_xpm)
		printf(RED"EA:"RESET"%s\n", game->map.ea_xpm);
	if (game->map.we_xpm)
		printf(RED"WE:"RESET"%s\n", game->map.we_xpm);
	if (game->map.ceiling_color[0])
		printf(GREEN"Ceiling:"RESET RED"R:"RESET"%d "RED"G:"RESET"%d "RED"B: " \
		RESET"%d\n", game->map.ceiling_color[0], game->map.ceiling_color[1],
			game->map.ceiling_color[2]);
	if (game->map.floor_color[0])
		printf(GREEN"Floor  :"RESET RED"R:"RESET"%d "RED"G:"RESET"%d "RED"B: " \
		RESET"%d\n", game->map.floor_color[0], game->map.floor_color[1],
			game->map.floor_color[2]);
	if (game->map.grid)
	{
		for(int i = 0; game->map.grid[i]; i++)
			printf(GREEN"line[%d]: length:[%d]"RESET ORG"	|%s|\n", i, game->map.widths[i], game->map.grid[i]);
		printf("longest line is: "RESET RED"%d\n"RESET, game->map.max_width);
		printf(ORG"Player pos: x: "RESET RED"%d"RESET ORG" y: " RESET RED"%d\n"RESET, game->ply.pos.x, game->ply.pos.y);
	}
}


void	initiate_map(t_map *map)
{
	map->resolution_x = 0;
	map->resolution_y = 0;
	map->no_xpm = NULL;
	map->so_xpm = NULL;
	map->ea_xpm = NULL;
	map->we_xpm = NULL;
	map->floor_color[0] = -1;
	map->floor_color[1] = -1;
	map->floor_color[2] = -1;
	map->grid = NULL;
	map->ceiling_color[0] = -1;
	map->ceiling_color[1] = -1;
	map->ceiling_color[2] = -1;
	map->map_height = 0;
	map->max_width = 0;
	map->widths = NULL;
	map->texture.no = NULL;
	map->texture.so = NULL;
	map->texture.ea = NULL;
	map->texture.we = NULL;
}

void	initiate_parser(t_game *game)
{
	game->parser.fd = 0;
	game->parser.line = NULL;
	game->parser.split = NULL;
	game->parser.map_part = false;
	game->parser.map = &game->map;
	game->parser.game = game;
}

void	initiate_player(t_game *game)
{
	game->ply.pos.x = 0;
	game->ply.pos.y = 0;
	game->ply.plyr_x = game->ply.pos.x * TILE_SIZE + TILE_SIZE / 2;
	game->ply.plyr_y = game->ply.pos.y * TILE_SIZE + TILE_SIZE / 2;
	game->ply.angle = 0;
	game->ply.fov_rd = (FOV * M_PI) / 180;
	game->ply.rot = 0;
	game->ply.l_r = 0;
	game->ply.u_d = 0;
}

void	initiate_ray(t_game *game)
{
	game->ray.index = 0;
	game->ray.ray_ngl = 0;
	game->ray.horiz_x = 0;
	game->ray.horiz_y = 0;
	game->ray.vert_x = 0;
	game->ray.vert_y = 0;
	game->ray.distance = 0;
	game->ray.flag = 0;
}

void	initiate_hud(t_game *game)
{
	game->hud.map = NULL;
	game->hud.pos = NULL;
	game->hud.circle = NULL;
	game->hud.circle_bck = NULL;
	game->hud.img_ci_bck = NULL;
	game->hud.ply = NULL;
	game->hud.img_ply = NULL;
	game->hud.w_dot = NULL;
	game->hud.b_dot = NULL;
	game->hud.img_wall = NULL;
	game->hud.img = NULL;
	game->hud.ply_flag = 0;
}

void	initiate_game(t_game *game)
{
	initiate_map(&game->map);
	initiate_parser(game);
	initiate_player(game);
	initiate_ray(game);
	// initiate_hud(game);
	game->scn.img = 0;
	game->mlx = NULL;
}

void	free_array(char **map)
{
	int		i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i++] = NULL;
	}
	free(map);
	map = NULL;
}

void	free_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
	texture = NULL;
}

void	free_map(t_map *map)
{
	if (map->no_xpm && map->no_xpm != NULL)
		free(map->no_xpm);
	if (map->no_xpm && map->so_xpm != NULL)
		free(map->so_xpm);
	if (map->ea_xpm && map->ea_xpm != NULL)
		free(map->ea_xpm);
	if (map->we_xpm && map->we_xpm != NULL)
		free(map->we_xpm);
	if (map->grid != NULL)
		free_array(map->grid);
	if (map->widths)
		free(map->widths);
	free_texture(map->texture.no);
	free_texture(map->texture.so);
	free_texture(map->texture.ea);
	free_texture(map->texture.we);
}

void	free_image(mlx_t *mlx, mlx_image_t *image)
{
	if (image)
		mlx_delete_image(mlx, image);
	image = NULL;
}

void	free_hud(t_game *game)
{
	if (game->mlx)
	{
		free_image(game->mlx, game->hud.circle);
		free_image(game->mlx, game->hud.circle_bck);
		free_image(game->mlx, game->hud.img_ci_bck);
		free_image(game->mlx, game->hud.img_ply);
		free_image(game->mlx, game->hud.img_wall);
	}
	free_texture(game->hud.w_dot);
	free_texture(game->hud.b_dot);
	free_texture(game->hud.ply);
	free_array(game->hud.map);
}

void	free_mlx(t_game *game)
{
	if (game->mlx != NULL)
	{
		mlx_delete_image(game->mlx, game->scn.img);
		mlx_close_window(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void 	free_raycast(t_ray *ray)
{
	(void)ray;
}

void	close_game(t_game *game)
{
	if (game != NULL)
	{
		free_map(&game->map);
		// free_hud(game);
		free_raycast(&game->ray);
		free_mlx(game);
		game = NULL;
		exit(EXIT_SUCCESS);
	}
}
