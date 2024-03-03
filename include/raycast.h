/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:02:39 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/29 10:51:49 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "../include/cub_3d.h"

typedef struct s_map t_map;
typedef struct s_game t_game;
typedef struct s_pos t_pos;


/*****************raycast_main.c********************/
void	game_loop(void *ml);	// game loop
void mlx_key(mlx_key_data_t keydata, void *ml);	// key press


#endif
