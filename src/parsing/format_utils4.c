/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:55:07 by flafi             #+#    #+#             */
/*   Updated: 2024/04/04 00:55:19 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	read_map(t_game *game)
{
	t_map	*map;

	map = game->parser.map;
	if (!all_chr_present(game->parser.line, MAPCHRS))
	{
		return (finish(game, "Map chars are incorrect!", NOSYSERR), 1);
	}
	game->parser.map_part = true;
	map->grid = ft_realloc_strings(map->grid, array_length(map->grid), \
			array_length(map->grid) + 1);
	map->grid[map->map_height] = ft_strdup(game->parser.line);
	map->grid[++map->map_height] = NULL;
	return (0);
}

bool	check_texture_file_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		return (true);
	}
	close(fd);
	return (false);
}

bool	check_element(t_parse *parser)
{
	t_map *map;

	map = parser->map;
	if ((map->no_xpm && check_texture_file_path(map->no_xpm)) && (map->so_xpm
			&& check_texture_file_path(map->so_xpm)) && (map->ea_xpm
			&& check_texture_file_path(map->ea_xpm)) && (map->we_xpm
			&& check_texture_file_path(map->we_xpm))
		&& ((map->ceiling_color[0] != -1) && (map->ceiling_color[1] != -1)
			&& (map->ceiling_color[02] != -1)) && ((map->floor_color[0] != -1)
			&& (map->floor_color[1] != -1) && (map->floor_color[2] != -1)))
	{
		return (true);
	}
	return (false);
}

int	check_map_char(t_game *game)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < game->map.map_height)
	{
		j = -1;
		while (++j < game->map.widths[i])
		{
			if (ft_strchr("NEWS", game->map.grid[i][j]) && game->ply.pos.x != 0)
				return (finish(game, "Repeated player char!", NOSYSERR), 1);
			if (ft_strchr("NEWS", game->map.grid[i][j]) && game->ply.pos.x == 0)
				game->ply.pos = (t_pos){j, i + 1};
		}
	}
	return (0);
}

int	calc_map_rows_widths(t_map *map)
{
	uint32_t	i;
	uint32_t	longest;

	i = -1;
	longest = 0;
	map->widths = (uint32_t *)ft_calloc(map->map_height, sizeof(uint32_t));
	while (++i < map->map_height)
	{
		map->widths[i] = ft_strlen(map->grid[i]);
		if (longest < map->widths[i])
			longest = map->widths[i];
	}
	map->max_width = longest;
	return (0);
}