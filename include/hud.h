/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:02:29 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/04/03 00:45:37 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "../include/cub_3d.h"

# define UP     1
# define DOWN   2
# define LEFT   3
# define RIGHT  4

typedef struct s_map	t_map;
typedef struct s_game	t_game;
typedef struct s_pos	t_pos;

/*****************hud_main.c********************/
bool	mini_map(t_game *game);
void	fill_map_circle(t_game	*game);
bool	mlx_initiate(t_game	*game);
void	pad_map_lines(char **map, uint32_t map_height,
			uint32_t longest_line, uint32_t *line_lengths);
#endif
