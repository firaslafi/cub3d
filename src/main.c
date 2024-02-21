/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: navid <navid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:16:02 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/21 05:29:25 by navid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

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
		printf(GREEN"Ceiling:"RESET RED"R:"RESET"%d "RED"G:"RESET"%d "RED"B: "
		RESET"%d\n", game->map.ceiling_color[0], game->map.ceiling_color[1],
			game->map.ceiling_color[2]);
	if (game->map.floor_color[0])
		printf(GREEN"Floor  :"RESET RED"R:"RESET"%d "RED"G:"RESET"%d "RED"B: "
		RESET"%d\n", game->map.floor_color[0], game->map.floor_color[1],
			game->map.floor_color[2]);
	if (game->map.grid)
	{
		for(int i = 0; game->map.grid[i]; i++)
			// printf(GREEN"%s\n"RESET, game->map.grid[i]);
			printf(GREEN"line[%d]: length:[%d]"RESET ORG"	|%s|\n", i, game->map.widths[i], game->map.grid[i]);
	printf("longest line is: "RESET RED"%d\n"RESET, game->map.max_width);
	}
}

bool	mlx_initiate(t_game	*game)
{
	game->mlx = mlx_init(MAX_WIDTH, MAX_HEIGHT, "cub3D", true);
	if (!game->mlx)
		return(error(game, "MLX is not initiated!!!", SYSERR), false);
	return (true);
}

void	game_run(t_game *game)
{
	mlx_initiate(game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (checking_map(ac, av, &game))
		return (close_game(&game), EXIT_FAILURE);
	print_map_details(&game);
	game_run(&game);
	return (close_game(&game), EXIT_SUCCESS);
}