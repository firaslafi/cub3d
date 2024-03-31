/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:02:29 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/03/06 06:10:06 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	start_the_game(t_game *game)	// start the game
{
	game->mlx = mlx_init(S_W, S_H, "Cub3D", 0);	// init the mlx pointer
	mini_map(game);
	raycast(game);
}

int main(int ac, char **av)	// main function
{
    t_game	game;
	
    if (checking_map(ac, av, &game))
		return (EXIT_FAILURE);
	print_map_details(&game);
	start_the_game(&game);	// start the game
	return (close_game(&game), EXIT_SUCCESS);
}
