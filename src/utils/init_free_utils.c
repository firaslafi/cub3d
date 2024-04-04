/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:54:10 by flafi             #+#    #+#             */
/*   Updated: 2024/04/04 01:59:33 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	free_image(mlx_t *mlx, mlx_image_t *image)
{
	if (image)
		mlx_delete_image(mlx, image);
	image = NULL;
}

void	free_hud(t_game *game)
{
	if (game->mlx)
	{
		free_image(game->mlx, game->hud.circle);
		free_image(game->mlx, game->hud.circle_bck);
		free_image(game->mlx, game->hud.img_ci_bck);
		free_image(game->mlx, game->hud.img_ply);
		free_image(game->mlx, game->hud.img_wall);
	}
}

void	free_mlx(t_game *game)
{
	if (game->mlx != NULL)
	{
		mlx_delete_image(game->mlx, game->scn.img);
		mlx_close_window(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_raycast(t_ray *ray)
{
	(void)ray;
}

void	close_game(t_game *game)
{
	if (game != NULL)
	{
		free_map(&game->map);
		free_hud(game);
		free_raycast(&game->ray);
		free_mlx(game);
		game = NULL;
		exit(EXIT_SUCCESS);
	}
}
