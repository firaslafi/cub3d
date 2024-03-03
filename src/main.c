/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:16:02 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/29 14:43:47 by nnabaeei         ###   ########.fr       */
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

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

void	game_run(t_game *game)
{
	mlx_initiate(game);
	// mlx_loop_hook(game->mlx, &game_loop, &game);	// game loop
	// mlx_key_hook(game->mlx, &mlx_key, &game);	// key press and release
	mini_map(game);
	mlx_loop(game->mlx);
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