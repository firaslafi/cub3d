
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:36 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/04/12 13:36:26 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

double take_ply_angel(t_game *game)
{
	if (game->map.grid[game->ply.pos.y - 1][game->ply.pos.x] == 'N')
		return (-M_PI / 2);
	if (game->map.grid[game->ply.pos.y - 1][game->ply.pos.x] == 'E')
		return (0);
	if (game->map.grid[game->ply.pos.y - 1][game->ply.pos.x] == 'W')
		return (M_PI);
	if (game->map.grid[game->ply.pos.y - 1][game->ply.pos.x] == 'S')
		return (M_PI / 2);
	return (0);
}