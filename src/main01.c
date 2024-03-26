/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:47:49 by flafi             #+#    #+#             */
/*   Updated: 2024/03/26 04:40:12 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub_3d.h"
#include <string.h>

#define S_W 1900
#define S_H 1000

//############################## THE MOUVEMENT CODE ##############################//


void	release_movement_keys(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->ply.l_r = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->ply.l_r = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->ply.u_d = 0;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->ply.u_d = 0;
}

void	release_rotation_keys(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->ply.rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->ply.rot = 0;
}

void	ft_reles(mlx_key_data_t keydata, t_game *game)
{
	release_movement_keys(game, keydata);
	release_rotation_keys(game, keydata);
}

void	mlx_key(mlx_key_data_t keydata, void *param) // key press
{
	t_game *game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT)) // exit the game
		finish(game, "finish game", MSG);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		// move left
		game->ply.l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		// move right
		game->ply.l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		// move down
		game->ply.u_d = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
		game->ply.u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		// rotate left
		game->ply.rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		// rotate right
		game->ply.rot = 1;
	ft_reles(keydata, game); // release the key
}

void	adjust_angle(double *angle)
{
	// Adjust angle to keep it within [0, 2π)
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
	while (*angle < 0)
		*angle += 2 * M_PI;
}
// rotate the player
void	rotate_player(t_game *game, int i)
{
	double rotation;

	if (i == 1)
	{
		rotation = ROTATION_SPEED; // rotate right
	}
	else
	{
		rotation = -ROTATION_SPEED; // rotate left
	}

	game->ply.angle += rotation;
	adjust_angle(&(game->ply.angle));
}


// move the player
void	move_player(t_game *game, double move_x, double move_y)
{
	// Calculate inverse of TILE_SIZE if not already calculated
	static const double inv_TILE_SIZE = 1.0 / TILE_SIZE;

	// Calculate new grid positions using integer arithmetic
	int new_x = round(game->ply.plyr_x + move_x);
	int new_y = round(game->ply.plyr_y + move_y);
	int map_grid_x = (int)(new_x * inv_TILE_SIZE);
	int map_grid_y = (int)(new_y * inv_TILE_SIZE);

	// Check for wall collisions
	if (game->map.grid[map_grid_y][map_grid_x] != '1'
		&& game->map.grid[(int)(new_y * inv_TILE_SIZE)][(int)(new_x
			* inv_TILE_SIZE)] != '1')
	{
		// Update player position
		game->ply.plyr_x = new_x;
		game->ply.plyr_y = new_y;
	}
}

// ********************************** // **********************************
// Helper function to calculate movement to the right
void	move_right(t_game *game, double *move_x, double *move_y)
{
	*move_x += -sin(game->ply.angle) * PLAYER_SPEED;
	*move_y += cos(game->ply.angle) * PLAYER_SPEED;
}

// Helper function to calculate movement to the left
void	move_left(t_game *game, double *move_x, double *move_y)
{
	*move_x += sin(game->ply.angle) * PLAYER_SPEED;
	*move_y += -cos(game->ply.angle) * PLAYER_SPEED;
}

// Helper function to calculate movement upwards
void	move_up(t_game *game, double *move_x, double *move_y)
{
	*move_x += cos(game->ply.angle) * PLAYER_SPEED;
	*move_y += sin(game->ply.angle) * PLAYER_SPEED;
}

// Helper function to calculate movement downwards
void	move_down(t_game *game, double *move_x, double *move_y)
{
	*move_x += -cos(game->ply.angle) * PLAYER_SPEED;
	*move_y += -sin(game->ply.angle) * PLAYER_SPEED;
}

// Main function to hook the player
void	hook(t_game *game, double move_x, double move_y)
{
	move_x = 0; // Reset movement variables
	move_y = 0;
	if (game->ply.rot == 1) // rotate right
		rotate_player(game, 1);
	else if (game->ply.rot == -1) // rotate left
		rotate_player(game, 0);
	if (game->ply.l_r == 1) // move right
		move_right(game, &move_x, &move_y);
	else if (game->ply.l_r == -1) // move left
		move_left(game, &move_x, &move_y);
	if (game->ply.u_d == 1) // move up
		move_up(game, &move_x, &move_y);
	else if (game->ply.u_d == -1) // move down
		move_down(game, &move_x, &move_y);
	move_player(game, move_x, move_y); // move the player
}
// **********************************// **********************************

//#####################################################################################//
//############################## THE WALL RENDERING CODE ##############################//
//#####################################################################################//

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0) // Check if x position is out of bounds
		x = 0;
	else if (x >= S_W)
		x = S_W - 1;
	if (y < 0) // Check if y position is out of bounds
		y = 0;
	else if (y >= S_H)
		y = S_H - 1;
	mlx_put_pixel(game->scn.img, x, y, color); // Put the pixel
}

float	nor_angle(float angle)
{
	// Normalize angle using modulo operation
	angle = fmod(angle, 2 * M_PI);
	// Ensure the result is within [0, 2π)
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)
// draw the floor and the ceiling
{
	int i;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(game, ray, i++, 0x005C4033); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game, ray, i++, 0xB99470FF); // ceiling
}

mlx_texture_t	*get_west_wall_color(t_game *game)
{
	return (game->map.texture.no); // Color for the west wall
}

mlx_texture_t	*get_east_wall_color(t_game *game)
{
	return (game->map.texture.no); // Color for the east wall
}

mlx_texture_t	*get_south_wall_color(t_game *game)
{
	return (game->map.texture.so); // Color for the south wall
}

mlx_texture_t	*get_north_wall_color(t_game *game)
{
	return (game->map.texture.so); // Color for the north wall
}

mlx_texture_t	*get_color(t_game *game, int flag)
{
	game->ray.ray_ngl = nor_angle(game->ray.ray_ngl); // Normalize the angle
	if (flag == 0)
	{
		// West wall
		if (game->ray.ray_ngl > M_PI / 2 && game->ray.ray_ngl < 3 * (M_PI / 2))
			return (get_west_wall_color(game));
		// East wall
		else
			return (get_east_wall_color(game));
	}
	else
	{
		// South wall
		if (game->ray.ray_ngl > 0 && game->ray.ray_ngl < M_PI)
			return (get_south_wall_color(game));
		// North wall
		else
			return (get_north_wall_color(game));
	}
}

double	get_x_o(mlx_texture_t *texture, t_game *game, double wall_distance)
{
	double	x_o;

	if (game->ray.flag == 1)
		x_o = fmod((game->ply.plyr_x + wall_distance * cos(game->ray.ray_ngl))
			* (texture->width / TILE_SIZE), texture->width);
	else
		x_o = fmod((game->ply.plyr_y + wall_distance * sin(game->ray.ray_ngl))
			* (texture->width / TILE_SIZE), texture->width);
	return (x_o);
}
// refractor this BITEEEEEEEEEEEEEE
int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	draw_wall(t_game *game, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_color(game, game->ray.flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, game, game->ray.distance);
	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(game, game->ray.index, t_pix,
			reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}
// to fix fish eye effect
double	adjust_distance(double distance, double cos_val)
{
	return (distance * cos_val);
}
// get the wall heigh obviously
double	calculate_wall_height(double distance, double tan_val)
{
	return (TILE_SIZE / distance) * ((S_W / 2) / tan_val);
}
/*to render the wall you need to get the top and bottom, position of the wall
on the screen do some crazy internet math that results in fish eye effect
that you need to fix with more internet math, then set the wall height
by gettunng top pixel and heigh maths and making sure the bottom is
on the ground the draw it includinh floor and ceiling according
to the input from the parsed .cub map*/
// fix fish eye effect
void	render_wall(t_game *game, int ray)
{
	double	wall_h;
	double	cos_val;
	double	tan_val;
	double	b_pix;
	double	t_pix;

	cos_val = cos(nor_angle(game->ray.ray_ngl - game->ply.angle));
	tan_val = tan(game->ply.fov_rd / 2);
	game->ray.distance = adjust_distance(game->ray.distance, cos_val);
	wall_h = calculate_wall_height(game->ray.distance, tan_val);
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H - 1;
	if (t_pix < 0)
		t_pix = 1;
	game->ray.index = ray;
	draw_wall(game, t_pix, b_pix, wall_h);
	draw_floor_ceiling(game, ray, t_pix, b_pix);
}

// ray casting section *****
// check the unit circle
int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

// check the intersection
int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
	}
	*step *= -1;
	return (1);
}
/*to check the wall hit we need ti get the x,y pos in the map
and do the raycasting maths*/
int	wall_hit(float x, float y, t_game *game)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if (y_m < 0 || y_m >= (int)game->map.map_height || x_m < 0
		|| x_m >= (int)game->map.max_width)
		return (0);
	if (game->map.grid[y_m][x_m] == '1')
		return (0);
	return (1);
}

float	get_h_inter(t_game *game, float angl)
{
	int		pixel;
	float	delta_x;
	float	delta_y;

	float h_x, h_y, x_step, y_step;
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(game->ply.plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = game->ply.plyr_x + (h_y - game->ply.plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y')
			&& x_step < 0))
		x_step *= -1;
	while (1)
	{
		if (!wall_hit(h_x, h_y - pixel, game))
			break ;
		h_x += x_step;
		h_y += y_step;
	}
	delta_x = h_x - game->ply.plyr_x;
	delta_y = h_y - game->ply.plyr_y;
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

// get the vertical intersection
float	calculate_distance(float v_x, float v_y, float plyr_x, float plyr_y)
{
	return (sqrt(pow(v_x - plyr_x, 2) + pow(v_y - plyr_y, 2)));
}

void	adjust_y_step(float *y_step, float angl)
{
	if ((unit_circle(angl, 'x') && *y_step < 0) || (!unit_circle(angl, 'x')
			&& *y_step > 0))
		*y_step *= -1;
}

void	move_to_next_intersection(float *v_x, float *v_y, float *x_step,
		float *y_step, t_game *game, int pixel)
{
	while (wall_hit(*v_x - pixel, *v_y, game))
	{
		*v_x += *x_step;
		*v_y += *y_step;
	}
}

float	get_v_inter(t_game *game, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(game->ply.plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = game->ply.plyr_y + (v_x - game->ply.plyr_x) * tan(angl);
	adjust_y_step(&y_step, angl);
	move_to_next_intersection(&v_x, &v_y, &x_step, &y_step, game, pixel);
	game->ray.vert_x = v_x;
	game->ray.vert_y = v_y;
	return (calculate_distance(v_x, v_y, game->ply.plyr_x, game->ply.plyr_y));
}
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

/* run the game loop, create new imgs,
	cast the rays put the image to the window*/
void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	mlx_delete_image(game->mlx, game->scn.img);
	game->scn.img = mlx_new_image(game->mlx, S_W, S_H);
	hook(game, 0, 0);
	cast_rays(game);
	mlx_image_to_window(game->mlx, game->scn.img, 0, 0);
}

// initializing and setting the player in the center of the tile X,Y
void	init_the_player(t_game *game)
{
	game->ply.plyr_x = game->ply.pos.x * TILE_SIZE + TILE_SIZE / 2;
	game->ply.plyr_y = game->ply.pos.y * TILE_SIZE + TILE_SIZE / 2;
	game->ply.fov_rd = (FOV * M_PI) / 180;
	game->ply.angle = M_PI;
}

// start the game, init player, run game loop and key hook
void	start_the_game(t_game *game)
{
	game->mlx = mlx_init(S_W, S_H, "Cub3D", 0);
	init_the_player(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, &mlx_key, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av) // main function
{
	t_game game;

	if (checking_map(ac, av, &game))
		return (EXIT_FAILURE);
	print_map_details(&game);
	start_the_game(&game); // start the game
	return (close_game(&game), EXIT_SUCCESS);
}
