/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:02:39 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/04/10 09:53:35 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "../include/cub_3d.h"

# define S_W 1900 // screen width
# define S_H 1000 // screen height

typedef struct s_map	t_map;
typedef struct s_game	t_game;
typedef struct s_pos	t_pos;
typedef struct s_intersection
{
	float	*v_x;
	float	*v_y;
	float	*x_step;
	float	*y_step;
	int		pixel;
}	t_intersection;

typedef struct s_vars
{
	float	vt_x;
	float	vt_y;
	float	x_step;
	float	y_step;
	int		pixel;
}	t_vars;

/*****************raycast_main.c********************/
void			raycasting_rendering(t_game *game);
void			release_movement_keys(t_game *game, mlx_key_data_t keydata);
void			release_rotation_keys(t_game *game, mlx_key_data_t keydata);
void			ft_reles(mlx_key_data_t keydata, t_game *game);
void			mlx_key(mlx_key_data_t keydata, void *param);
void			adjust_angle(double *angle);
void			rotate_player(t_game *game, int i);
void			move_player(t_game *game, double move_x, double move_y);
void			move_right(t_game *game, double *move_x, double *move_y);
void			move_left(t_game *game, double *move_x, double *move_y);
void			move_up(t_game *game, double *move_x, double *move_y);
void			move_down(t_game *game, double *move_x, double *move_y);
void			hook(t_game *game, double move_x, double move_y);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
float			nor_angle(float angle);
uint32_t		rgb_to_uint32(int *rgb);
void			draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix);
mlx_texture_t	*get_west_wall_color(t_game *game);
mlx_texture_t	*get_east_wall_color(t_game *game);
mlx_texture_t	*get_south_wall_color(t_game *game);
mlx_texture_t	*get_north_wall_color(t_game *game);
mlx_texture_t	*get_color(t_game *game, int flag);
// double	get_x_o(mlx_texture_t *texture, t_game *game, double wall_distance);
int				reverse_bytes(int c);
void			draw_wall(t_game *game, int t_pix, int b_pix, double wall_h);
void			render_wall(t_game *game, int ray);
int				unit_circle(float angle, char c);
// int		inter_check(float angle, float *inter, float *step, int is_horizon);
int				wall_hit(float x, float y, t_game *game);
float			get_h_inter(t_game *game, float angl);
// float	calculate_distance(float v_x, float v_y, float plyr_x, float plyr_y)
void			adjust_y_step(float *y_step, float angl);
void			move_to_next_intersection(t_intersection *inter, t_game *game);
float			get_v_inter(t_game *game, float angl);
void			game_loop(void *param);
void			init_the_player(t_game *game);
t_intersection	init_intersection(t_vars *vars);
int				intersek_chck(float angle, float *inter, float *step,
					int is_horizon);
double			adjust_distance(double distance, double cos_val);
double			calculate_wall_height(double distance, double tan_val);
mlx_texture_t	*get_textures(t_game *game, int flag);
double			get_x_pos(mlx_texture_t *texture, t_game *game, \
				double wall_distance);
void			ref_mlx_pixel_put(t_game *game, int x, int y, int color);
uint32_t		rev_byte(uint32_t c);
#endif
