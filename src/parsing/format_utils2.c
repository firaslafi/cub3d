/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:48:02 by flafi             #+#    #+#             */
/*   Updated: 2024/04/04 00:48:43 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

char	**rm_empty_array_elements(char **str_array)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	while (str_array[j] != NULL)
	{
		if (str_array[j++][0] != '\0')
			i++;
	}
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (str_array[++i] != NULL)
	{
		if (str_array[i][0] != '\0')
			result[j++] = str_array[i];
		else
			free(str_array[i]);
	}
	result[j] = NULL;
	return (free(str_array), result);
}

size_t	ft_strcountchr(char *str, char c)
{
	int		i;
	size_t	counter;

	i = -1;
	counter = 0;
	while (str[++i])
	{
		if (str[i] == c)
			counter++;
	}
	return (counter);
}

int	extract_rgb(t_parse *parser)
{
	char	**rgb;

	if (ft_strcountchr(parser->split[1], ',') > 2)
		return (finish(parser->game, "Wrong rgb format!!!", NOSYSERR));
	rgb = ft_split(parser->split[1], ',');
	if (array_length(rgb) != 3)
		return (free_array(rgb), 1);
	if (!ft_strcmp(parser->split[0], "F"))
	{
		parser->map->floor_color[0] = check_digit(rgb[0]);
		parser->map->floor_color[1] = check_digit(rgb[1]);
		parser->map->floor_color[2] = check_digit(rgb[2]);
	}
	else if (!ft_strcmp(parser->split[0], "C"))
	{
		parser->map->ceiling_color[0] = check_digit(rgb[0]);
		parser->map->ceiling_color[1] = check_digit(rgb[1]);
		parser->map->ceiling_color[2] = check_digit(rgb[2]);
	}
	return (free_array(rgb), 0);
}

int	read_element(t_parse *parser)
{
	int	j;

	j = 0;
	parser->split = ft_split(parser->line, ' ');
	while (parser->split[j] != NULL)
	{
		str_trim(parser->split[j], '\t');
		j++;
	}
	parser->split = rm_empty_array_elements(parser->split);
	if (array_length(parser->split) != 2)
		return (free_array(parser->split), 1);
	if (ft_strcmp(parser->split[0], "NO") == 0)
		parser->map->no_xpm = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "SO") == 0)
		parser->map->so_xpm = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "EA") == 0)
		parser->map->ea_xpm = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "WE") == 0)
		parser->map->we_xpm = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "F") == 0
		|| ft_strcmp(parser->split[0], "C") == 0)
		extract_rgb(parser);
	return (free_array(parser->split), 0);
}

bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(WHITSPACE, line[i++]))
			return (false);
	}
	return (true);
}
