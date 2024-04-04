/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:53:04 by flafi             #+#    #+#             */
/*   Updated: 2024/04/04 01:49:47 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

bool	assessment_map(t_game *game)
{
	calc_map_rows_widths(&game->map);
	check_map_char(game);
	check_map_path(game);
	return (true);
}

bool	assessment_element(t_game *game, int err)
{
	int		i;
	t_map	*map;

	map = &game->map;
	if (!map->no_xpm || !check_texture_file_path(map->no_xpm))
		return (finish(game, "NO_texture file add wrong", err), false);
	if (!map->so_xpm || !check_texture_file_path(map->so_xpm))
		return (finish(game, "SO_texture file add wrong", err), false);
	if (!map->ea_xpm || !check_texture_file_path(map->ea_xpm))
		return (finish(game, "EA_texture file add wrong", err), false);
	if (!map->we_xpm || !check_texture_file_path(map->we_xpm))
		return (finish(game, "WE_texture file add wrong", err), false);
	i = 0;
	while (map->ceiling_color[i])
	{
		if (map->ceiling_color[i++] == -1)
			return (finish(game, "Ceiling color is wrong", err), false);
	}
	i = 0;
	while (map->floor_color[i])
	{
		if (map->floor_color[i++] == -1)
			return (finish(game, "Floor color is wrong", err), false);
	}
	return (true);
}

bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

int	check_digit(char *color)
{
	if (!is_numeric(color))
		return (-1);
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255)
	{
		return (-1);
	}
	return (ft_atoi(color));
}

void	str_trim(char *str, char ch)
{
	char	*src;
	char	*dst;

	src = str;
	dst = str;
	if (str == NULL)
		return ;
	while (*src != '\0')
	{
		if (*src != ch)
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}
