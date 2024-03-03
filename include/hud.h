/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:02:29 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/03/02 04:19:46 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HUD_H
# define HUD_H

# include "../include/cub_3d.h"

# define UP     1
# define DOWN   2
# define LEFT   3
# define RIGHT  4

typedef struct s_map t_map;
typedef struct s_game t_game;
typedef struct s_pos t_pos;


/*****************hud_main.c********************/
bool    mini_map(t_game *game);
bool	mlx_initiate(t_game	*game);
void hud_move_hook(mlx_key_data_t keydata, void* param);
#endif
