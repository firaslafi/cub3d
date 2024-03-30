/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:14:49 by flafi             #+#    #+#             */
/*   Updated: 2024/03/30 23:15:34 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

mlx_texture_t	*get_west_wall_color(t_game *game)
{
	return (game->map.texture.we);
}

mlx_texture_t	*get_east_wall_color(t_game *game)
{
	return (game->map.texture.ea);
}

mlx_texture_t	*get_south_wall_color(t_game *game)
{
	return (game->map.texture.so);
}

mlx_texture_t	*get_north_wall_color(t_game *game)
{
	return (game->map.texture.no);
}

mlx_texture_t	*get_textures(t_game *game, int flag)
{
	game->ray.ray_ngl = nor_angle(game->ray.ray_ngl);
	if (flag == 0)
	{
		if (game->ray.ray_ngl > M_PI / 2 && game->ray.ray_ngl < 3 * (M_PI / 2))
			return (get_west_wall_color(game));
		else
			return (get_east_wall_color(game));
	}
	else
	{
		if (game->ray.ray_ngl > 0 && game->ray.ray_ngl < M_PI)
			return (get_south_wall_color(game));
		else
			return (get_north_wall_color(game));
	}
}
