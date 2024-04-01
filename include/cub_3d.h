/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:26:06 by flafi             #+#    #+#             */
/*   Updated: 2024/03/31 14:26:06 by flafi            ###   ########.fr       */
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
# include <limits.h>
# ifdef __linux__
	# include <X11/X.h>
# endif
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/fts.h"
# include "../include/utils.h"
# include "../include/parser.h"
# include "../include/hud.h"
# include "../include/raycast.h"

# define BLUE		"\033[38;5;4m"
# define GREEN		"\033[38;5;2m"  // For a bright green try 10 instead of 2
# define ORG		"\033[38;5;214m"
# define RED		"\033[38;5;196m"
# define RESET		"\033[0m"

# define SYSERR		0
# define NOSYSERR	1
# define MSG		2
// # define WIDTH 256
// # define HEIGHT 256
#define MINIMAP_RADIUS 10
#define MINIMAP_CENTER 130

# define TILE_SIZE 40 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.08 // rotation speed
# define PLAYER_SPEED 8	// player speed

typedef struct s_parse t_parse;


# define	 S_W 800
# define S_H 600
# define WIN_WIDTH  1900
# define WIN_HEIGHT 1000
# define DOT_SIZE	10

static const double inv_TILE_SIZE = 1.0 / TILE_SIZE;

typedef struct s_intersection
{
    float *v_x;
    float *v_y;
    float *x_step;
    float *y_step;
    int pixel;
} t_intersection;

typedef struct s_vars
{
    float vt_x;
    float vt_y;
    float x_step;
    float y_step;
    int pixel;
} t_vars;

typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_tex;

typedef struct s_map{
	int			resolution_x;
	int			resolution_y;
	char		*no_xpm;
	char		*so_xpm;
	char		*we_xpm;
	char		*ea_xpm;
	// char		*sprite_texture;
	int			floor_color[3];
	char		**grid;
	int			ceiling_color[3];
	// uint32_t	map_width;
	uint32_t	map_height;
	uint32_t	max_width;
	uint32_t	*widths;
	t_tex		texture;
}		t_map;

typedef struct s_parse{
    
    int     fd;
    char    *line;
    char    **split;
    bool    map_part;
    t_map   *map;
	t_game	*game;
} 		t_parse;

typedef struct s_pos{
	uint32_t	x;
	uint32_t	y;
}		t_pos;

typedef struct s_player{
	t_pos		pos;
	int			plyr_x; // player x position in pixels
	int			plyr_y; // player y position in pixels
	double		angle;	// player angle
	float		fov_rd;	// field of view in radians
	int			rot;	// rotation flag
	int			l_r;	// left right flag
	int			u_d;	// up down flag
}		t_player;


typedef struct s_scene{
	mlx_image_t		*img;
}	t_scene;

typedef struct s_hud{
	char			**map;
	t_pos			pos;
	mlx_image_t		*circle;
	mlx_image_t		*circle_bck;
	mlx_image_t		*img_ci_bck;
	mlx_texture_t	*ply;
	mlx_image_t		*img_ply;
	mlx_texture_t	*w_dot;
	mlx_texture_t	*b_dot;
	mlx_image_t		*img_wall;
	int				ply_flag;
}	t_hud;

typedef struct s_ray	//the ray structure
{
	int		index;
	double	ray_ngl;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;	// distance to the wall
	int		flag;		// flag for the wall
}	t_ray;

typedef struct s_game{
	t_map		map;
	t_parse		parser;
	t_player	ply;
	t_ray		ray;
	t_hud		hud;
	t_scene		scn;
	mlx_t		*mlx;

}		t_game;

/////////////////////////////////////////////////////
////                     utils                  /////
/////////////////////////////////////////////////////

mlx_texture_t	*get_textures(t_game *game, int flag);
float	nor_angle(float angle);
void	rotate_player(t_game *game, int i);
void	adjust_angle(double *angle);
void	move_player(t_game *game, double move_x, double move_y);
void	hook(t_game *game, double move_x, double move_y);
void	move_right(t_game *game, double *move_x, double *move_y);
void	move_left(t_game *game, double *move_x, double *move_y);
void	move_up(t_game *game, double *move_x, double *move_y);
void	move_down(t_game *game, double *move_x, double *move_y);
void	cast_rays(t_game *game);
float	get_v_inter(t_game *game, float angl);
float	get_h_inter(t_game *game, float angl);
void	render_wall(t_game *game, int ray);
int	unit_circle(float angle, char c);
int	intersek_chck(float angle, float *inter, float *step, int is_horizon);
int	wall_hit(float x, float y, t_game *game);
double	calculate_wall_height(double distance, double tan_val);
double	adjust_distance(double distance, double cos_val);
void	draw_wall(t_game *game, int t_pix, int b_pix, double wall_h);
void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix);
uint32_t	rev_byte(uint32_t c);
double	get_x_pos(mlx_texture_t *texture, t_game *game, double wall_distance);
void	ref_mlx_pixel_put(t_game *game, int x, int y, int color);
t_intersection	init_intersection(t_vars *vars);
#endif