/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:47:49 by flafi             #+#    #+#             */
/*   Updated: 2024/03/25 10:22:21 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub_3d.h"
#include <string.h>

#define S_W 1900 // screen width
#define S_H 1000 // screen height


typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_tex;

typedef struct s_data // the data structure
{
	char **map2d; // the map game->map.grid
	int p_x;      // player x position in the map game->ply.pos.x
	int p_y;      // player y position in the map
	int w_map;    // map width
	int h_map;    // map height
	t_tex *texture;
}					t_data;

typedef struct s_mlx // the mlx structure
{
	mlx_image_t *img; // the image
	mlx_t *mlx_p;     // the mlx pointer
	t_ray *ray;       // the ray structure
	t_data *dt;       // the data structure
	t_player *ply;    // the player structure
	t_tex *texture;

}					t_mlx;

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

void	mlx_key(mlx_key_data_t keydata, void *ml) // key press
{
	t_game *game;

	game = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT)) // exit the game
		finish(game, "finish game", NOSYSERR);
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

void	rotate_player(t_game *game, int i) // rotate the player
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

	// Adjust the angle
	adjust_angle(&(game->ply.angle));
}

void	move_player(t_game *game, double move_x, double move_y)
		// move the player
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

//############################## THE WALL RENDERING CODE ##############################//

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
		// Pass the wall distance as the third argument
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

void	render_wall(t_game *game, int ray)
{
	double	wall_h;
	double	cos_val;
	double	tan_val;

	double b_pix; // bottom pixel position of the wall on the screen
	double t_pix; // top pixel position of the wall on the screen
	cos_val = cos(nor_angle(game->ray.ray_ngl - game->ply.angle));
	tan_val = tan(game->ply.fov_rd / 2);
	game->ray.distance *= cos_val;                                    
		// fix the fisheye
	wall_h = (TILE_SIZE / game->ray.distance) * ((S_W / 2) / tan_val);
		// get the wall height
	b_pix = (S_H / 2) + (wall_h / 2);                                 
		// get the bottom pixel
	t_pix = (S_H / 2) - (wall_h / 2);                                 
		// get the top pixel
	// Ensure bottom and top pixels are within screen bounds
	if (b_pix > S_H)
		b_pix = S_H - 1;
	if (t_pix < 0)
		t_pix = 1;
	game->ray.index = ray;
	draw_wall(game, t_pix, b_pix, wall_h);       // draw the wall
	draw_floor_ceiling(game, ray, t_pix, b_pix);
		// draw the floor and the ceiling
}

//############################## THE RAYCASTING CODE ##############################//

int	unit_circle(float angle, char c) // check the unit circle
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

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
 // check the intersection
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

int	wall_hit(float x, float y, t_game *game) // check the wall hit
{
	uint32_t x_m;
	uint32_t y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE); // get the x position in the map
	y_m = floor(y / TILE_SIZE); // get the y position in the map
	if (y_m >= game->map.map_height || x_m >= game->map.max_width)
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

void	cast_rays(t_game *game) // cast the rays
{
	double h_inter;
	double v_inter;
	int ray;

	ray = 0;
	game->ray.ray_ngl = game->ply.angle - (game->ply.fov_rd / 2);
		// the start angle
	while (ray < S_W)                                            
		// loop for the rays
	{
		game->ray.flag = 0;                                       
			// flag for the wall
		h_inter = get_h_inter(game, nor_angle(game->ray.ray_ngl));
			// get the horizontal intersection
		v_inter = get_v_inter(game, nor_angle(game->ray.ray_ngl));
			// get the vertical intersection
		if (v_inter <= h_inter)                                   
			// check the distance
			game->ray.distance = v_inter;                         
				// get the distance
		else
		{
			game->ray.distance = h_inter; // get the distance
			game->ray.flag = 1;           // flag for the wall
		}

		render_wall(game, ray);                        // render the wall
		ray++;                                         // next ray
		game->ray.ray_ngl += (game->ply.fov_rd / S_W); // next angle
	}
}

//############################## START THE GAME AND THE GAME LOOP ##############################//

void	game_loop(void *ml) // game loop
{
	t_game *game;

	game = ml; // cast to the mlx structure
	printf("hiiiiii2222222222222222222\n");
	mlx_delete_image(game->mlx, game->scn.img);          // delete the image
	game->scn.img = mlx_new_image(game->mlx, S_W, S_H);  // create new image
	hook(game, 0, 0);                                    // hook the player
	cast_rays(game);                                     // cast the rays
	mlx_image_to_window(game->mlx, game->scn.img, 0, 0);
		// put the image to the window
}


void	start_the_game(t_game *game) // start the game
{
	// t_mlx	mlx;
	// t_game  *game;

	// mlx.dt = dt;	// init the mlx structure
	// game->ply = (t_player *)calloc(1,
			sizeof(t_player));	// init the player structure i'm using calloc to initialize the variables to zero
	// mlx.ray = calloc(1, sizeof(t_ray));	// init the ray structure
	// mlx.mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);	// init the mlx pointer
	game->mlx = mlx_init(S_W, S_H, "Cub3D", 0); // init the mlx pointer
	mlx_loop_hook(game->mlx, &game_loop, game); // game loop
	mlx_key_hook(game->mlx, &mlx_key, game);    // key press and release
	mlx_loop(game->mlx);                        // mlx loop
}

//############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//



// int main()	// main function
// {
t_game				game;

if	(checking_map(ac, av, &game))
	return (EXIT_FAILURE);
print_map_details(&game);
start_the_game(&data, &game); // start the game
return (close_game(&game), EXIT_SUCCESS);

return (0);
;
// }
