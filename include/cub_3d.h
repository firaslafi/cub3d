/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:29:06 by nnavidd           #+#    #+#             */
/*   Updated: 2024/02/09 23:11:25 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB_3D_H
# define CUB_3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <sys/wait.h>
# include <limits.h>
# include <X11/X.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/fts.h"
# include "../include/utils.h"
# include "../include/parser.h"


# define WIDTH 256
# define HEIGHT 256



# define MAX_WIDTH  1024
# define MAX_HEIGHT 1024

typedef struct s_map{
	int		resolution_x;
	int		resolution_y;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*sprite_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**grid;
	int		map_width;
	int		map_height;
}		t_map;

typedef struct s_game{
	t_map	*map;
}	t_game;

/////////////////////////////////////////////////////
////                     utils                  /////
/////////////////////////////////////////////////////



#endif