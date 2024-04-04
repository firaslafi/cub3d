/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:56:59 by flafi             #+#    #+#             */
/*   Updated: 2024/04/04 02:00:23 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	initiate_hud(t_game *game)
{
	game->hud.map = NULL;
	game->hud.pos = (t_pos){0, 0};
	game->hud.circle = NULL;
	game->hud.circle_bck = NULL;
	game->hud.img_ci_bck = NULL;
	game->hud.ply = NULL;
	game->hud.img_ply = NULL;
	game->hud.w_dot = NULL;
	game->hud.b_dot = NULL;
	game->hud.img_wall = NULL;
	game->hud.ply_flag = 0;
}

void	initiate_game(t_game *game, char *file)
{
	initiate_map(&game->map);
	initiate_parser(&game->parser, game, file);
	initiate_player(game);
	initiate_ray(game);
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
