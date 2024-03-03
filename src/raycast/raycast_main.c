// before you start, you need to install the mlx library and you need to install the glfw library
// you need to incude the mlx library in your file
// for compiling the code you need to include the required frameworks and the libmlx.a amd link the glfw library
// the flag (-O3 -ffast-math) is for optimization
// the flag (-framework) is for the required frameworks
// the flag (-lglfw) is for linking the glfw library
// the flag (-L) is for the path to the glfw library
// the flag (-o) is for the name of the executable file
// to run the program (./cub)

// example:
// cc -O3 -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw (path to libmlx42.a) -L(path to glfw library) cub3d.c -o cub

// # include <string.h>
// # include <stdlib.h>
// # include <stdio.h>
// # include <math.h>
// # include "MLX/MLX42.h" // include the mlx library
# include "../include/raycast.h" 

// # define WIN_WIDTH 1900 // screen wimaph
// # define WIN_HEIGHT 1000 // screen height


// typedef struct s_player //the player structure
// {
// 	int		plyr_x; // player x position in pixels
// 	int		plyr_y; // player y position in pixels
// 	double	angle;	// player angle
// 	float	fov_rd;	// field of view in radians
// 	int		rot;	// rotation flag
// 	int		l_r;	// left right flag
// 	int		u_d;	// up down flag
// }	t_player;

// typedef struct s_ray	//the ray structure
// {
// 	double	ray_ngl;	// ray angle
// 	double	distance;	// distance to the wall
// 	int		flag;		// flag for the wall
// }	t_ray;

// typedef struct s_data	//the data structure
// {
// 	char	**grid;	// the map
// 	int		pos.x;		// player x position in the map
// 	int		pos.y;		// player y position in the map
// 	int		w_map;		// map wimaph
// 	int		h_map;		// map height
// }	t_map;

// typedef struct s_game	//the mlx structure
// {
// 	mlx_image_t		*img;	// the image
// 	mlx_t			*mlx_p;	// the mlx pointer
// 	t_ray			*ray;	// the ray structure
// 	t_map			*map;	// the data structure
// 	t_player		*ply;	// the player structure
// }	t_game;

//##############################################################################//
//############################## THE EXITING CODE ##############################//
//##############################################################################//

void	ft_exit(t_game *game) 		// exit the game
{
	// int	i = 0;
	// while (game->map->grid[i])
	// 	free(game->map->grid[i++]); // free the map line by line
	// free(game->map->grid); // free the map
	// free(game->map); // free the data structure
	// free(game->ply); // free the player structure
	// free(game->ray); // free the ray structure
	mlx_delete_image(game->mlx, game->scn.img); // delete the image
	mlx_close_window(game->mlx); // close the window
	mlx_terminate(game->mlx); // terminate the mlx pointer
	printf("Game closed\n"); // print the message
	exit(0); // exit the game
}

//################################################################################//
//############################## THE MOUVEMENT CODE ##############################//
//################################################################################//

void	ft_reles(mlx_key_data_t keydata, t_game *game)	// release the key
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game->ply.l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game->ply.l_r = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game->ply.u_d = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		game->ply.u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->ply.rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->ply.rot = 0;
}

void mlx_key(mlx_key_data_t keydata, void *ml)	// key press
{
	t_game *game;

	game = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
		ft_exit(game);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
		game->ply.l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
		game->ply.l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
		game->ply.u_d = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
		game->ply.u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
		game->ply.rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
		game->ply.rot = 1;
	ft_reles(keydata, game); // release the key
}

void	rotate_player(t_game *game, int i)	// rotate the player
{
	if (i == 1)
	{
		game->ply.angle += ROTATION_SPEED; // rotate right
		if (game->ply.angle > 2 * M_PI)
			game->ply.angle -= 2 * M_PI;
	}
	else
	{
		game->ply.angle -= ROTATION_SPEED; // rotate left
		if (game->ply.angle < 0)
			game->ply.angle += 2 * M_PI;
	}
}

void	move_player(t_game *game, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(game->ply.plyr_x + move_x); // get the new x position
	new_y = roundf(game->ply.plyr_y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (game->map.grid[map_grid_y][map_grid_x] != '1' && \
	(game->map.grid[map_grid_y][game->ply.plyr_x / TILE_SIZE] != '1' && \
	game->map.grid[game->ply.plyr_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		game->ply.plyr_x = new_x; // move the player
		game->ply.plyr_y = new_y; // move the player
	}
}

void	hook(t_game *game, double move_x, double move_y)	// hook the player
{
	if (game->ply.rot == 1) //rotate right
		rotate_player(game, 1);
	if (game->ply.rot == -1) //rotate left
		rotate_player(game, 0);
	if (game->ply.l_r == 1) //move right
	{
		move_x = -sin(game->ply.angle) * PLAYER_SPEED;
		move_y = cos(game->ply.angle) * PLAYER_SPEED;
	}
	if (game->ply.l_r == -1) //move left
	{
		move_x = sin(game->ply.angle) * PLAYER_SPEED;
		move_y = -cos(game->ply.angle) * PLAYER_SPEED;
	}
	if (game->ply.u_d == 1) //move up
	{
		move_x = cos(game->ply.angle) * PLAYER_SPEED;
		move_y = sin(game->ply.angle) * PLAYER_SPEED;
	}
	if (game->ply.u_d == -1) //move down
	{
		move_x = -cos(game->ply.angle) * PLAYER_SPEED;
		move_y = -sin(game->ply.angle) * PLAYER_SPEED;
	}
	move_player(game, move_x, move_y); // move the player
}

//#####################################################################################//
//############################## THE WALL RENDERING CODE ##############################//
//#####################################################################################//

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)	// put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= WIN_WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= WIN_HEIGHT)
		return ;
	mlx_put_pixel(game->scn.img, x, y, color); // put the pixel
}

float	nor_angle(float angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;
	// int		c;

	i = b_pix;
	while (i < WIN_HEIGHT)
		my_mlx_pixel_put(game, ray, i++, 0xB99470FF); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game, ray, i++, 0x89CFF3FF); // ceiling
}

int	get_color(t_game *game, int flag)	// get the color of the wall
{
	game->ray.ray_ngl = nor_angle(game->ray.ray_ngl); // normalize the angle
	if (flag == 0)
	{
		if (game->ray.ray_ngl > M_PI / 2 && game->ray.ray_ngl < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (game->ray.ray_ngl > 0 && game->ray.ray_ngl < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void	draw_wall(t_game *game, int ray, int t_pix, int b_pix)	// draw the wall
{
	int color;

	color = get_color(game, game->ray.flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(game, ray, t_pix++, color);
}

void	render_wall(t_game *game, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game->ray.distance *= cos(nor_angle(game->ray.ray_ngl - game->ply.angle)); // fix the fisheye
	wall_h = (TILE_SIZE / game->ray.distance) * ((WIN_WIDTH / 2) / tan(game->ply.fov_rd / 2)); // get the wall height
	b_pix = (WIN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (WIN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > WIN_HEIGHT) // check the bottom pixel
		b_pix = WIN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(game, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(game, ray, t_pix, b_pix); // draw the floor and the ceiling
}

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

int	unit_circle(float angle, char c)	// check the unit circle
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

int	inter_check(float angle, float *inter, float *step, int iWIN_HEIGHTorizon)	// check the intersection
{
	if (iWIN_HEIGHTorizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_game *game)	// check the wall hit
{
	uint32_t		x_m;
	uint32_t		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = (uint32_t)floor (x / TILE_SIZE); // get the x position in the map
	y_m = (uint32_t)floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= game->map.map_height || x_m >= game->map.max_width)) // there is not any fixed map width
		return (0);
	if (game->map.grid[y_m] && x_m <= (uint32_t)strlen(game->map.grid[y_m]))
		if (game->map.grid[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_game *game, float angl)	// get the horizontal intersection
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(game->ply.plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = game->ply.plyr_x + (h_y - game->ply.plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, game)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - game->ply.plyr_x, 2) + pow(h_y - game->ply.plyr_y, 2))); // get the distance
}

float	get_v_inter(t_game *game, float angl)	// get the vertical intersection
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE; 
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(game->ply.plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
	v_y = game->ply.plyr_y + (v_x - game->ply.plyr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, game)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - game->ply.plyr_x, 2) + pow(v_y - game->ply.plyr_y, 2))); // get the distance
}

void	cast_rays(t_game *game)	// cast the rays
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	game->ray.ray_ngl = game->ply.angle - (game->ply.fov_rd / 2); // the start angle
	while (ray < WIN_WIDTH) // loop for the rays
	{
		game->ray.flag = 0; // flag for the wall
		h_inter = get_h_inter(game, nor_angle(game->ray.ray_ngl)); // get the horizontal intersection
		v_inter = get_v_inter(game, nor_angle(game->ray.ray_ngl)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			game->ray.distance = v_inter; // get the distance
		else
		{
			game->ray.distance = h_inter; // get the distance
			game->ray.flag = 1; // flag for the wall
		}
		render_wall(game, ray); // render the wall
		ray++; // next ray
		game->ray.ray_ngl += (game->ply.fov_rd / WIN_WIDTH); // next angle
	}
}

//##############################################################################################//
//############################## START THE GAME AND THE GAME LOOP ##############################//
//##############################################################################################//

void	game_loop(void *ml)	// game loop
{
	t_game *game;

	game = ml;	// cast to the mlx structure
	mlx_delete_image(game->mlx, game->scn.img);	// delete the image
	game->scn.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);	// create new image
	hook(game, 0, 0); // hook the player
	cast_rays(game);	// cast the rays
	mlx_image_to_window(game->mlx, game->scn.img, 0, 0); // put the image to the window
}

void init_the_player(t_game *game)	// init the player structure
{
	game->ply.plyr_x = game->ply.pos.x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	game->ply.plyr_y = game->ply.pos.y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	game->ply.fov_rd = (FOV * M_PI) / 180; // field of view in radians
	game->ply.angle = M_PI; // player angle
	//the rest of the variables are initialized to zero by calloc
}

// void	start_the_game(t_map *map)	// start the game
// {
// 	t_game *game

// 	mlx.map = map;	// init the mlx structure
// 	mlx.ply = calloc(1, sizeof(t_player));	// init the player structure i'm using calloc to initialize the variables to zero
// 	mlx.ray = calloc(1, sizeof(t_ray));	// init the ray structure
// 	mlx.mlx_p = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", 0);	// init the mlx pointer
// 	init_the_player(mlx);	// init the player structure
// 	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);	// game loop
// 	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);	// key press and release
// 	mlx_loop(mlx.mlx_p);	// mlx loop
// }

// //################################################################################################//
// //############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//
// //################################################################################################//

// t_map *init_argumet()	// init the data structure
// {
// 	t_map *map = calloc(1, sizeof(t_map)); // init the data structure
// 	map->grid = calloc(10, sizeof(char *)); // init the map
// 	map->grid[0] = strdup("1111111111111111111111111"); //fill the map
// 	map->grid[1] = strdup("1000000000000000000100001");
// 	map->grid[2] = strdup("1001000000000P00000000001");
// 	map->grid[3] = strdup("1001000000000000001000001");
// 	map->grid[4] = strdup("1001000000000000001000001");
// 	map->grid[5] = strdup("1001000000100000001000001");
// 	map->grid[6] = strdup("1001000000000000001000001");
// 	map->grid[7] = strdup("1001000000001000001000001");
// 	map->grid[8] = strdup("1111111111111111111111111");
// 	map->grid[9] = NULL;
// 	map->pos.y = 3; // player y position in the map
// 	map->pos.x = 14; // player x position in the map
// 	map->w_map = 25; // map wimaph
// 	map->h_map = 9; // map height
// 	return (map); // return the data structure
// }

// int main()	// main function
// {
// 	t_map	*data;

// 	data = init_argumet();	// init the data structure
// 	start_the_game(data);	// start the game
// 	return 0;
// }