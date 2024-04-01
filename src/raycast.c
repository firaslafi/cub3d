/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:51:03 by flafi             #+#    #+#             */
/*   Updated: 2024/04/02 01:51:04 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub_3d.h"

// cast the rays
/* ray angle gets the starting angel and then we loop through the rays
we initialize the wall flag to 0, (no wall until we really find a wall)
get both horizontal and vertical intersection then we check the distance
between the intersection and we get the distance if v <= h we set V as
distance else it is H and we flag for a wall we loop through all the
rays and angels updating them of course
*/
void	cast_rays(t_game *game)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	game->ray.ray_ngl = game->ply.angle - (game->ply.fov_rd / 2);
	while (ray < S_W)
	{
		game->ray.flag = 0;
		h_inter = get_h_inter(game, nor_angle(game->ray.ray_ngl));
		v_inter = get_v_inter(game, nor_angle(game->ray.ray_ngl));
		if (v_inter <= h_inter)
			game->ray.distance = v_inter;
		else
		{
			game->ray.distance = h_inter;
			game->ray.flag = 1;
		}
		render_wall(game, ray);
		ray++;
		game->ray.ray_ngl += (game->ply.fov_rd / S_W);
	}
}
