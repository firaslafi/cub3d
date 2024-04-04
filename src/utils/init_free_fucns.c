/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_fucns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:02:04 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/04/04 01:59:15 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

// void print_map_details(t_game *game)
// {
// 	if (game->map.no_xpm)
// 		printf(RED"NO:"RESET"%s\n", game->map.no_xpm);
// 	if (game->map.so_xpm)
// 		printf(RED"SO:"RESET"%s\n", game->map.so_xpm);
// 	if (game->map.ea_xpm)
// 		printf(RED"EA:"RESET"%s\n", game->map.ea_xpm);
// 	if (game->map.we_xpm)
// 		printf(RED"WE:"RESET"%s\n", game->map.we_xpm);
// 	if (game->map.ceiling_color[0])
// 		printf(GREEN"Ceiling:"RESET RED"R:"RESET"%d "RED"G:"RESET"%d "RED"B: "
// 		RESET"%d\n", game->map.ceiling_color[0], game->map.ceiling_color[1],
// 			game->map.ceiling_color[2]);
// 	if (game->map.floor_color[0])
// 		printf(GREEN"Floor  :"RESET RED"R:"RESET"%d "RED"G:"RESET"%d "RED"B: "
// 		RESET"%d\n", game->map.floor_color[0], game->map.floor_color[1],
// 			game->map.floor_color[2]);
// 	if (game->map.grid)
// 	{
// 		for(int i = 0; game->map.grid[i]; i++)
// 			printf(GREEN"line[%d]: length:[%d]"RESET ORG"	
// |%s|\n", i, game->map.widths[i], game->map.grid[i]);
// 	printf("longest line is: "RESET RED"%d\n"RESET, game->map.max_width);
// 	printf(ORG"Player pos: x: "RESET RED"%d"RESET ORG" y: 
// " RESET RED"%d\n"RESET, game->ply.pos.x, game->ply.pos.y);
// 	}
// }

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

void	initiate_parser(t_parse *parser, t_game *game, char *file)
{
	parser->fd = open(file, O_RDONLY);
	if (parser->fd == -1)
		finish(game, "The cub file address is wrong.", SYSERR);
	parser->line = NULL;
	parser->split = NULL;
	parser->map_part = false;
	parser->map = &game->map;
	parser->game = game;
}

void	initiate_player(t_game *game)
{
	game->ply.pos.x = 0;
	game->ply.pos.y = 0;
	game->ply.plyr_x = game->ply.pos.x * TILE_SIZE + TILE_SIZE / 2;
	game->ply.plyr_y = game->ply.pos.y * TILE_SIZE + TILE_SIZE / 2;
	game->ply.angle = M_PI;
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
