/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:23:22 by nnavidd           #+#    #+#             */
/*   Updated: 2024/03/03 18:32:35 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

/*This func calls nowhere, just created to
check the created sample map.*/
void print_grid(char **grid)
{
	int	i = 0;

	while (grid[i] != NULL)
	{
		ft_printf(ORG"%d:%s|\n"RESET,i, grid[i]);
		i++;
	}
	if (write(1,"\n",1) < 0)
		return ;
}

char	**creat_sample_gird(t_game *game)
{
	char	**grid;
	int		i;

	grid = (char **) ft_calloc(game->map.map_height + 1, sizeof(char *));
	if (!grid)
		return (finish(game, "Malloc error!!!", SYSERR), NULL);
	i = -1;
	while(game->map.grid[++i] != 0)
		grid[i] = ft_strdup(game->map.grid[i]);
	grid[i] = NULL;
	return (grid);
}

bool fill_grid(t_game *game, t_pos pos, char **grid)
{
	if ((int)pos.y < 0 || pos.y >= game->map.map_height || \
		(int)pos.x < 0 || pos.x >= game->map.widths[pos.y])
	{
		return (finish(game, "Wrong path in Map!!!", NOSYSERR));
	}
	if (grid[pos.y][pos.x] == '1')
		return true;
	if (grid[pos.y][pos.x] == ' ')
		grid[pos.y][pos.x] = '0';
	grid[pos.y][pos.x] = '1';
	fill_grid(game, (t_pos){pos.x - 1, pos.y}, grid);
	fill_grid(game, (t_pos){pos.x + 1, pos.y}, grid);
	fill_grid(game, (t_pos){pos.x, pos.y + 1}, grid);
	fill_grid(game, (t_pos){pos.x, pos.y - 1}, grid);
	return true;
}

/*To check the path we need to create a sample map
of the taken map to check if the created floor
goes to exit part and all coins or not.*/
int check_map_path(t_game *game)
{
	char **grid;

	if (game->map.grid == NULL)
		finish(game, "No Map found!!!", NOSYSERR);
	grid = creat_sample_gird(game);
	if (!fill_grid(game, game->ply.pos, grid))
		return (free_array(grid), finish(game, "Map has wrong path!!!", NOSYSERR));
	free_array(grid);
	return (0);
}
