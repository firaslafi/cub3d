/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:36 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/03/04 22:34:53 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

size_t	array_length(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL || !*array)
		return (0);
	while(array[i])
		i++;
	return (i);
}

bool	all_chr_present(char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while(s2[j])
		{
			if (s1[i] == s2[j])
				break;
			j++;
		}
		if (s1[i] != s2[j])
			return (false);
		i++;
	}
	return (true);
}

/* This function reallocate an array of string from its old size to its
 new size.*/
uint32_t *ft_realloc_int(uint32_t *input, size_t old_count, size_t new_count)
{
	uint32_t	*new_ptr;
	size_t		i;

	if (!input)
	{
		new_ptr = (uint32_t *)ft_calloc(new_count + 1, sizeof(uint32_t));
		if (!new_ptr)
			return NULL;
		return (new_ptr);
	}

	new_ptr = (uint32_t *)ft_calloc(new_count + 1, sizeof(uint32_t));
	if (!new_ptr)
		return (free(input),NULL);
	i = -1;
	while (++i < old_count)
		new_ptr[i] = input[i];
	free(input);
	return new_ptr; // Return the new memory block
}

char	**ft_realloc_strings(char **ptr, size_t old_count, size_t new_count)
{
	char	**new_ptr;
	size_t	i;

	if (!ptr)
	{
		new_ptr = (char **) ft_calloc(new_count + 1, sizeof(char *));
		if (!new_ptr)
			return (free_array(new_ptr), NULL);
		return (new_ptr);
	}
	new_ptr = ft_calloc(old_count + new_count + 1, sizeof(char *));
	if (new_ptr == NULL)
		return (free_array(ptr), NULL);
	i = -1;
	while (++i < old_count)
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		if (new_ptr[i] == NULL)
			return (free_array(new_ptr), NULL);
	}
	free_array(ptr);
	return (new_ptr);
}

size_t list_len(uint32_t *arr)
{
	size_t	count;

	count = 0;
	while (arr && *arr)
	{
		count++;
		arr++;
	}
	return (count);
}

int read_map(t_game *game)
{
	
	// (void)parser;
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

bool check_element(t_parse *parser)
{
	// int		fd;
	t_map	*map;
	
	map = parser->map;
	if ((map->no_xpm && check_texture_file_path(map->no_xpm)) &&
		(map->so_xpm && check_texture_file_path(map->so_xpm)) &&
		(map->ea_xpm && check_texture_file_path(map->ea_xpm)) &&
		(map->we_xpm && check_texture_file_path(map->we_xpm)) &&
		((map->ceiling_color[0] != -1) && (map->ceiling_color[1] != -1) &&
		(map->ceiling_color[02] != -1)) && ((map->floor_color[0] != -1) &&
		(map->floor_color[1] != -1) && (map->floor_color[2] != -1)))
		{
			// printf("check element is true line is: %s\n", parser->line);
			return ( true);
		}
	// printf("check element is false\n");
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
	// for (uint32_t i = 0; i < map->map_height; i++)
	// 	printf("line[%d]: length:[%d]	|%s|\n", i, map->widths[i], map->grid[i]);
	// printf(GREEN"longest line is: "RESET RED"%d\n"RESET, map->max_width);
	return (0);
}


bool	assessment_map(t_game *game)
{
	// printf("hight:%d, line[%d]:%s\n", m->map_height, m->map_height, m->grid[m->map_height]);
	calc_map_rows_widths(&game->map);
	check_map_char(game);
	check_map_path(game);
	return (true);
}

bool assessment_element(t_game *game, int err)
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

bool is_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			// printf("string color:%s\n", str);
			return (false);
		}
		i++;
	}
	return (true);
}

int	check_digit(char  *color)
{
	if (!is_numeric(color))
		return (-1);
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255)
	{
		// printf("is not a in a range:%d\n", ft_atoi(color));
		return (-1);
	}
	// printf("the color num:%d\n", ft_atoi(color));
	return (ft_atoi(color));
}

void str_trim(char *str, char ch)
{
	char *src;
	char *dst;

	src = str;
	dst = str;
	if (str == NULL)
		return;
	while (*src != '\0')
	{
		if (*src != ch)
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

char **rm_empty_array_elements(char **str_array)
{
	int 	i;
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
		return NULL;
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
	int	i;
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

int extract_rgb(t_parse *parser)
{
	char	**rgb;

	if (ft_strcountchr(parser->split[1], ',') > 2)
		return (finish(parser->game, "Wrong rgb format!!!", NOSYSERR));
	rgb = ft_split(parser->split[1], ',');
	// for (int  i =  0; rgb[i]; i++)
	// 	printf("rgb[%d]:%s\n", i, rgb[i]);
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
	
	// printf(RED"no_file:%s\n"RESET, parser->map->no_xpm);
	parser->split = ft_split(parser->line, ' ');
	for (int j = 0; parser->split[j] != NULL; j++)
		str_trim(parser->split[j], '\t');
	parser->split = rm_empty_array_elements(parser->split);
	// for(int i = 0; parser->split[i]; i++)
	// 			printf("\ts[%d]:%s.\n", i, parser->split[i]);
	if (array_length(parser->split) != 2)
		return (free_array(parser->split), 1);
	if (ft_strcmp(parser->split[0] ,"NO") == 0)
		parser->map->no_xpm = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "SO") == 0)
		parser->map->so_xpm = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "EA") == 0)
		parser->map->ea_xpm = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "WE") == 0)
		parser->map->we_xpm = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "F") == 0 || 
				ft_strcmp(parser->split[0], "C") == 0)
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

int	fetch_map_detail(t_game *game)
{
	int li = 0;
	
	while ((game->parser.line = get_next_line(game->parser.fd)))
	{
		li++;
		if (game->parser.line[ft_strlen(game->parser.line) -1] == '\n')
			game->parser.line[ft_strlen(game->parser.line) - 1] = '\0';
		if (!game->parser.line)
			continue ;
		if (!line_is_empty(game->parser.line))
		{

			if (check_element(&game->parser))
				read_map(game);
			read_element(&game->parser);
		}
		else if (line_is_empty(game->parser.line) && game->parser.map_part)
			finish(game, "Empty line during map reading!!!", NOSYSERR);
		if (game->parser.line)
			free(game->parser.line);
	}
	close(game->parser.fd);
	return (EXIT_SUCCESS);
}

int	assessment_png_file(t_game *game)
{
	if ((game->map.texture.no = mlx_load_png(game->map.no_xpm)) == NULL)
		return (finish(game, "North PNG file data worng!", NOSYSERR));
	if ((game->map.texture.so = mlx_load_png(game->map.so_xpm)) == NULL)
		return (finish(game, "South PNG file data worng!", NOSYSERR));
	if ((game->map.texture.ea = mlx_load_png(game->map.ea_xpm)) == NULL)
		return (finish(game, "East PNG file data worng!", NOSYSERR));
	if ((game->map.texture.we = mlx_load_png(game->map.we_xpm)) == NULL)
		return (finish(game, "West PNG file data worng!", NOSYSERR));
	return(EXIT_SUCCESS);
}

int	parsing_map(t_game *game)
{
	fetch_map_detail(game);
	assessment_element(game, NOSYSERR);
	assessment_png_file(game);
	assessment_map(game);
	pad_map_lines(game->map.grid, game->map.map_height, game->map.max_width, game->map.widths);
	return (EXIT_SUCCESS);
}

int	check_map_file_format_add(t_game *game, char *file)
{
	char	*str;
	int		i;
	int		j;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (finish(game, "Cub file address is wrong!", SYSERR));
	close(fd);
	str = ft_strdup(".cub\0");
	i = (int)ft_strlen(file) - 4;
	j = 0;
	if (i < 0)
		return (free(str), finish(game, "Cub file format wrong!", NOSYSERR));
	while (file[i] != '\0' && str[j] != '\0')
	{
		if (file[i++] != str[j++])
			return (free(str), finish(game, "Cub file format wrong!", NOSYSERR));
	}
	if (file[i] == '\0' && str[j] == '\0')
		return (free(str), EXIT_SUCCESS);
	else
		return (free(str), finish(game, "Cub file format wrong!", NOSYSERR)); 
}

int	checking_map(int ac, char **av, t_game *game)
{
	if (ac != 2)
		return (finish(game, "Wrong input numbers!", NOSYSERR), EXIT_FAILURE);
	initiate_game(game, av[1]);
	if (check_map_file_format_add(game, av[1]))
		return (EXIT_FAILURE);
	if (parsing_map(game))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}