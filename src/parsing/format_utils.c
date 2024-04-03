/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:12:46 by flafi             #+#    #+#             */
/*   Updated: 2024/04/04 01:05:21 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	fetch_map_detail(t_game *game)
{
	int	li;

	li = 0;
	game->parser.line = get_next_line(game->parser.fd);
	while (game->parser.line)
	{
		li++;
		if (game->parser.line[ft_strlen(game->parser.line) - 1] == '\n')
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
		game->parser.line = get_next_line(game->parser.fd);
	}
	close(game->parser.fd);
	return (EXIT_SUCCESS);
}

int	assessment_png_file(t_game *game)
{
	game->map.texture.no = mlx_load_png(game->map.no_xpm);
	if (game->map.texture.no == NULL)
		return (finish(game, "North PNG file data wrong!", NOSYSERR));
	game->map.texture.so = mlx_load_png(game->map.so_xpm);
	if (game->map.texture.so == NULL)
		return (finish(game, "South PNG file data wrong!", NOSYSERR));
	game->map.texture.ea = mlx_load_png(game->map.ea_xpm);
	if (game->map.texture.ea == NULL)
		return (finish(game, "East PNG file data wrong!", NOSYSERR));
	game->map.texture.we = mlx_load_png(game->map.we_xpm);
	if (game->map.texture.we == NULL)
		return (finish(game, "West PNG file data wrong!", NOSYSERR));
	return (EXIT_SUCCESS);
}

int	parsing_map(t_game *game)
{
	fetch_map_detail(game);
	assessment_element(game, NOSYSERR);
	assessment_png_file(game);
	assessment_map(game);
	pad_map_lines(game->map.grid, game->map.map_height,
		game->map.max_width, game->map.widths);
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
			return (free(str),
				finish(game, "Cub file format wrong!", NOSYSERR));
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
