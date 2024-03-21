/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:47:49 by flafi             #+#    #+#             */
/*   Updated: 2024/03/13 22:30:55 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/MLX42/include/MLX42/MLX42.h"
#include "../libs/libft/libft/libft.h"
// #include "./main.h"
#include <fcntl.h>
#include <stdio.h>
#include "../include/cub_3d.h"
# include <string.h>


# define S_W 1900 // screen width
# define S_H 1000 // screen height
// # define TILE_SIZE 40 // tile size
// # define FOV 60 // field of view
// # define ROTATION_SPEED 0.03 // rotation speed
// # define PLAYER_SPEED 3	// player speed

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

// typedef struct s_ray
// {
// 	int		index;
// 	double	ray_ngl;
// 	double	horiz_x;
// 	double	horiz_y;
// 	double	vert_x;
// 	double	vert_y;
// 	double	distance;
// 	int		flag;
// }	t_ray;


// typedef struct s_tex
// {
// 	mlx_texture_t	*no;
// 	mlx_texture_t	*so;
// 	mlx_texture_t	*we;
// 	mlx_texture_t	*ea;
// }	t_tex;

typedef struct s_data	//the data structure
{
	char	**map2d;	// the map game->map.grid
	int		p_x;		// player x position in the map game->ply.pos.x
	int		p_y;		// player y position in the map
	int		w_map;		// map width
	int		h_map;		// map height
    // t_tex   *texture;
}	t_data;

typedef struct s_mlx	//the mlx structure
{
	mlx_image_t		*img;	// the image
	mlx_t			*mlx_p;	// the mlx pointer
	t_ray			*ray;	// the ray structure
	t_data			*dt;	// the data structure
	t_player		*ply;	// the player structure
    t_tex           texture;
    
}	t_mlx;

//##############################################################################//
//############################## THE EXITING CODE ##############################//
//##############################################################################//

void	ft_exit(t_mlx *mlx) 		// exit the game
{
	// int	i = 0;
	// while (mlx->dt->map2d[i])
		// free(mlx->dt->map2d[i++]); // free the map line by line
	// free(mlx->dt->map2d); // free the map
	// free(mlx->dt); // free the data structure
	// free(mlx->ply); // free the player structure
	// free(mlx->ray); // free the ray structure
	mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
	// mlx_close_window(mlx->mlx_p); // close the window
	// mlx_terminate(mlx->mlx_p); // terminate the mlx pointer
	printf("Game closed\n"); // print the message
	exit(0); // exit the game
}

//################################################################################//
//############################## THE MOUVEMENT CODE ##############################//
//################################################################################//

void release_movement_keys(t_mlx *mlx, mlx_key_data_t keydata) {
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
        mlx->ply->l_r = 0;
    else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
        mlx->ply->l_r = 0;
    else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
        mlx->ply->u_d = 0;
    else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
        mlx->ply->u_d = 0;
}

void release_rotation_keys(t_mlx *mlx, mlx_key_data_t keydata) {
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
        mlx->ply->rot = 0;
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
        mlx->ply->rot = 0;
}

void ft_reles(mlx_key_data_t keydata, t_mlx *mlx) {
    release_movement_keys(mlx, keydata);
    release_rotation_keys(mlx, keydata);
}

void mlx_key(mlx_key_data_t keydata, void *ml)	// key press
{
	t_mlx	*mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
		ft_exit(mlx);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
		mlx->ply->l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
		mlx->ply->l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
		mlx->ply->u_d = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
		mlx->ply->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
		mlx->ply->rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
		mlx->ply->rot = 1;
	ft_reles(keydata, mlx); // release the key
}

void adjust_angle(double *angle) {
    // Adjust angle to keep it within [0, 2π)
    while (*angle >= 2 * M_PI)
        *angle -= 2 * M_PI;
    while (*angle < 0)
        *angle += 2 * M_PI;
}

void	rotate_player(t_mlx *mlx, int i)	// rotate the player
{
    double rotation;

    if (i == 1) {
        rotation = ROTATION_SPEED; // rotate right
    } else {
        rotation = -ROTATION_SPEED; // rotate left
    }

    mlx->ply->angle += rotation;

 // Adjust the angle
    adjust_angle(&(mlx->ply->angle));

}


void	move_player(t_mlx *mlx, double move_x, double move_y)	// move the player
{
    // Calculate inverse of TILE_SIZE if not already calculated
    static const double inv_TILE_SIZE = 1.0 / TILE_SIZE;

    // Calculate new grid positions using integer arithmetic
    int new_x = round(mlx->ply->plyr_x + move_x);
    int new_y = round(mlx->ply->plyr_y + move_y);
    int map_grid_x = (int)(new_x * inv_TILE_SIZE);
    int map_grid_y = (int)(new_y * inv_TILE_SIZE);

    // Check for wall collisions
    if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' &&
        mlx->dt->map2d[(int)(new_y * inv_TILE_SIZE)][(int)(new_x * inv_TILE_SIZE)] != '1') {
        // Update player position
        mlx->ply->plyr_x = new_x;
        mlx->ply->plyr_y = new_y;
    }
}

// ********************************** // **********************************
// Helper function to calculate movement to the right
void move_right(t_mlx *mlx, double *move_x, double *move_y) {
    *move_x += -sin(mlx->ply->angle) * PLAYER_SPEED;
    *move_y += cos(mlx->ply->angle) * PLAYER_SPEED;
}

// Helper function to calculate movement to the left
void move_left(t_mlx *mlx, double *move_x, double *move_y) {
    *move_x += sin(mlx->ply->angle) * PLAYER_SPEED;
    *move_y += -cos(mlx->ply->angle) * PLAYER_SPEED;
}

// Helper function to calculate movement upwards
void move_up(t_mlx *mlx, double *move_x, double *move_y) {
    *move_x += cos(mlx->ply->angle) * PLAYER_SPEED;
    *move_y += sin(mlx->ply->angle) * PLAYER_SPEED;
}

// Helper function to calculate movement downwards
void move_down(t_mlx *mlx, double *move_x, double *move_y) {
    *move_x += -cos(mlx->ply->angle) * PLAYER_SPEED;
    *move_y += -sin(mlx->ply->angle) * PLAYER_SPEED;
}

// Main function to hook the player
void hook(t_mlx *mlx, double move_x, double move_y) {
    move_x = 0; // Reset movement variables
    move_y = 0;

    if (mlx->ply->rot == 1) // rotate right
        rotate_player(mlx, 1);
    else if (mlx->ply->rot == -1) // rotate left
        rotate_player(mlx, 0);

    if (mlx->ply->l_r == 1) // move right
        move_right(mlx, &move_x, &move_y);
    else if (mlx->ply->l_r == -1) // move left
        move_left(mlx, &move_x, &move_y);

    if (mlx->ply->u_d == 1) // move up
        move_up(mlx, &move_x, &move_y);
    else if (mlx->ply->u_d == -1) // move down
        move_down(mlx, &move_x, &move_y);

    move_player(mlx, move_x, move_y); // move the player
}
// **********************************// **********************************

//#####################################################################################//
//############################## THE WALL RENDERING CODE ##############################//
//#####################################################################################//


void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color) {
    if (x < 0) // Check if x position is out of bounds
        x = 0;
    else if (x >= S_W)
        x = S_W - 1;

    if (y < 0) // Check if y position is out of bounds
        y = 0;
    else if (y >= S_H)
        y = S_H - 1;


    mlx_put_pixel(mlx->img, x, y, color); // Put the pixel
}

float nor_angle(float angle) {
    // Normalize angle using modulo operation
    angle = fmod(angle, 2 * M_PI);
    
    // Ensure the result is within [0, 2π)
    if (angle < 0)
        angle += 2 * M_PI;
    
    return angle;
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, 0x005C4033); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, 0xB99470FF); // ceiling
}
    
mlx_texture_t *get_west_wall_color(t_mlx *mlx) {
    return mlx->texture.no; // Color for the west wall
}

mlx_texture_t *get_east_wall_color(t_mlx *mlx) {
    return mlx->texture.no; // Color for the east wall
}

mlx_texture_t *get_south_wall_color(t_mlx *mlx) {
    return mlx->texture.so;; // Color for the south wall
}

mlx_texture_t *get_north_wall_color(t_mlx *mlx) {
    return mlx->texture.so;; // Color for the north wall
}

mlx_texture_t *get_color(t_mlx *mlx, int flag) {
    

    mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // Normalize the angle

    if (flag == 0) {

        // West wall
        if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
            return get_west_wall_color(mlx);
        // East wall
        else
            return get_east_wall_color(mlx);
    } else {
        // South wall
        if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
            return get_south_wall_color(mlx);
        // North wall
        else
            return get_north_wall_color(mlx);
    }
}

double get_x_o(mlx_texture_t *texture, t_mlx *mlx, double wall_distance)
{
    double x_o;

    if (mlx->ray->flag == 1)
        x_o = fmod((mlx->ply->plyr_x + wall_distance * cos(mlx->ray->ray_ngl)) * (texture->width / TILE_SIZE), texture->width);
    else
        x_o = fmod((mlx->ply->plyr_y + wall_distance * sin(mlx->ray->ray_ngl)) * (texture->width / TILE_SIZE), texture->width);
    
    return x_o;
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
void draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
    double x_o;
    double y_o;
    mlx_texture_t *texture;
    uint32_t *arr;
    double factor;

    texture = get_color(mlx, mlx->ray->flag);
    arr = (uint32_t *)texture->pixels;
    factor = (double)texture->height / wall_h;
    x_o = get_x_o(texture, mlx, mlx->ray->distance); // Pass the wall distance as the third argument
    y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
    if (y_o < 0)
        y_o = 0;
    while (t_pix < b_pix)
    {
        my_mlx_pixel_put(mlx, mlx->ray->index, t_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
        y_o += factor;
        t_pix++;
    }
}


void render_wall(t_mlx *mlx, int ray) {
    double wall_h;
    double b_pix; // bottom pixel position of the wall on the screen
    double t_pix; // top pixel position of the wall on the screen

    double cos_val = cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle));
    double tan_val = tan(mlx->ply->fov_rd / 2);

    mlx->ray->distance *= cos_val; // fix the fisheye
    wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan_val); // get the wall height
    b_pix = (S_H / 2) + (wall_h / 2); // get the bottom pixel
    t_pix = (S_H / 2) - (wall_h / 2); // get the top pixel

    // Ensure bottom and top pixels are within screen bounds
    if (b_pix > S_H)
        b_pix = S_H - 1;
    if (t_pix < 0)
        t_pix = 1;
        
    mlx->ray->index = ray;
    draw_wall(mlx, t_pix, b_pix, wall_h); // draw the wall
    draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
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

int inter_check(float angle, float *inter, float *step, int is_horizon) { // check the intersection
    if (is_horizon) {
        if (angle > 0 && angle < M_PI) {
            *inter += TILE_SIZE;
            return -1;
        }
    } else {
        if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) {
            *inter += TILE_SIZE;
            return -1;
        }
    }
    *step *= -1;
    return 1;
}

int	wall_hit(float x, float y, t_mlx *mlx)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if (y_m < 0 || y_m >= mlx->dt->h_map || x_m < 0 || x_m >= mlx->dt->w_map)
		return 0;

	if (mlx->dt->map2d[y_m][x_m] == '1')
		return 0;
	return (1);
}

float get_h_inter(t_mlx *mlx, float angl) {
    float h_x, h_y, x_step, y_step;
    int pixel;

    y_step = TILE_SIZE;
    x_step = TILE_SIZE / tan(angl);
    h_y = floor(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angl, &h_y, &y_step, 1);
    h_x = mlx->ply->plyr_x + (h_y - mlx->ply->plyr_y) / tan(angl);
    
    if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0))
        x_step *= -1;

    while (1) {
        if (!wall_hit(h_x, h_y - pixel, mlx))
            break;
        
        h_x += x_step;
        h_y += y_step;
    }

    float delta_x = h_x - mlx->ply->plyr_x;
    float delta_y = h_y - mlx->ply->plyr_y;
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

// get the vertical intersection
float calculate_distance(float v_x, float v_y, float plyr_x, float plyr_y) {
    return sqrt(pow(v_x - plyr_x, 2) + pow(v_y - plyr_y, 2));
}

void adjust_y_step(float *y_step, float angl) {
    if ((unit_circle(angl, 'x') && *y_step < 0) || (!unit_circle(angl, 'x') && *y_step > 0))
        *y_step *= -1;
}

void move_to_next_intersection(float *v_x, float *v_y, float *x_step, float *y_step, t_mlx *mlx, int pixel) {
    while (wall_hit(*v_x - pixel, *v_y, mlx)) {
        *v_x += *x_step;
        *v_y += *y_step;
    }
}

float get_v_inter(t_mlx *mlx, float angl) {
    float v_x;
    float v_y;
    float x_step;
    float y_step;
    int pixel;

    x_step = TILE_SIZE;
    y_step = TILE_SIZE * tan(angl);
    v_x = floor(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angl, &v_x, &x_step, 0);
    v_y = mlx->ply->plyr_y + (v_x - mlx->ply->plyr_x) * tan(angl);

    adjust_y_step(&y_step, angl);

    move_to_next_intersection(&v_x, &v_y, &x_step, &y_step, mlx, pixel);
    mlx->ray->vert_x = v_x;
	mlx->ray->vert_y = v_y;
    return calculate_distance(v_x, v_y, mlx->ply->plyr_x, mlx->ply->plyr_y);
}

void	cast_rays(t_mlx *mlx)	// cast the rays
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2); // the start angle
	while (ray < S_W) // loop for the rays
	{
		mlx->ray->flag = 0; // flag for the wall
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			mlx->ray->distance = v_inter; // get the distance
		else
		{
			mlx->ray->distance = h_inter; // get the distance
			mlx->ray->flag = 1; // flag for the wall
		}
		render_wall(mlx, ray); // render the wall
		ray++; // next ray
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W); // next angle
	}
}

//##############################################################################################//
//############################## START THE GAME AND THE GAME LOOP ##############################//
//##############################################################################################//

void	game_loop(void *ml)	// game loop
{
	t_mlx	*mlx;

	mlx = ml;	// cast to the mlx structure
	mlx_delete_image(mlx->mlx_p, mlx->img);	// delete the image
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);	// create new image
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);	// create new image
	hook(mlx, 0, 0); // hook the player
	cast_rays(mlx);	// cast the rays
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0); // put the image to the window
}

void init_the_player(t_mlx mlx)	// init the player structure
{
	mlx.ply->plyr_x = mlx.dt->p_x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	mlx.ply->plyr_y = mlx.dt->p_y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	mlx.ply->fov_rd = (FOV * M_PI) / 180; // field of view in radians
	mlx.ply->angle = M_PI; // player angle
	//the rest of the variables are initialized to zero by calloc
}

void	start_the_game(t_data *dt, t_game *game)	// start the game
{
	t_mlx	mlx;
    // t_game  game;

	mlx.dt = dt;	// init the mlx structure
    game->mlx = mlx_init(S_W, S_H, "Cub3D", 0);	// init the mlx pointer
	// mlx.ply = calloc(1, sizeof(t_player));	// init the player structure i'm using calloc to initialize the variables to zero
	// mlx.ray = calloc(1, sizeof(t_ray));	// init the ray structure
	// initiate_player(&game);
    // initiate_ray(&game);
	mlx.ply = &game->ply;
	mlx.ray = &game->ray;
    mlx.mlx_p = game->mlx;
    game->scn.img = mlx.img;
    mlx.texture.no = game->map.texture.no;
    mlx.texture.so = game->map.texture.so;
    mlx.texture.ea = game->map.texture.no;
    mlx.texture.we = game->map.texture.no;
    // mlx.texture = (t_tex *)(malloc(sizeof(t_tex)));  // move to init argument
    // mlx.texture->no = mlx_load_png("./texture/stone_wall.png"); // this texture
    // mlx.texture->so = mlx_load_png("./texture/wolf.png");
	init_the_player(mlx);	// init the player structure
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);	// game loop
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);	// key press and release
    mlx_loop(mlx.mlx_p);	// mlx loop
}

//################################################################################################//
//############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//
//################################################################################################//

// t_data *init_argumet()	// init the data structure
// {
// 	t_data *dt = calloc(1, sizeof(t_data)); // init the data structure
// 	dt->map2d = calloc(10, sizeof(char *)); // init the map
// 	dt->map2d[0] = strdup("1111111111111111111111111\0"); //fill the map
// 	dt->map2d[1] = strdup("1000000000000000000100001\0");
// 	dt->map2d[2] = strdup("1001000000000P00000000001\0");
// 	dt->map2d[3] = strdup("1001000000000000001000001\0");
// 	dt->map2d[4] = strdup("1001000000000000001000001\0");
// 	dt->map2d[5] = strdup("1001000000100000001000001\0");
// 	dt->map2d[6] = strdup("1001000000000000001000001\0");
// 	dt->map2d[7] = strdup("1001000000001000001000001\0");
// 	dt->map2d[8] = strdup("1111111111111111111111111\0");
// 	// dt->map2d[9] = NULL;
// 	dt->p_y = 3; // player y position in the map
// 	dt->p_x = 14; // player x position in the map
// 	dt->w_map = 25; // map width
// 	dt->h_map = 9; // map height
// 	return (dt); // return the data structure
// }


int main(int ac, char **av)	// main function
{
    t_game	game;
	
    if (checking_map(ac, av, &game))
		return (EXIT_FAILURE);
	print_map_details(&game);
    
    t_data	data;
	// data = init_argumet();	// init the data structure

	data.map2d = game.map.grid;
    data.p_y = game.ply.pos.y;	// init the data structure
    data.p_x = game.ply.pos.x;	// init the data structure
    data.w_map = game.map.max_width;
    data.h_map = game.map.map_height;

    // data.texture = (t_tex *)(malloc(sizeof(t_tex)));  // move to init argument
    // data.texture->no = mlx_load_png("./texture/stone_wall.png");
    // data.texture->so = mlx_load_png("./texture/wolf.png");
	start_the_game(&data, &game);	// start the game
	return (close_game(&game), EXIT_SUCCESS);



	
	return 0;
}


//gcc raycast.c ./libs/MLX42/build/libmlx42.a ./libs/libft/libft.a -Iinclude -ldl -lglfw -pthread -lm -fsanitize=address -o navid