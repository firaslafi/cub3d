

#include "../include/hud.h"

// bool 	draw_minimap(t_game *game)
// {
// 	uint32_t	i;
// 	uint32_t	j;
// 	i = 0;
// 	while (i < game->map.map_height)
// 	{
// 		j = 0;
// 		while (j <= game->map.widths[i])
// 		{
// 			if (game->map.grid[i][j] == '0')
// 			{
// 				// mlx_put_pixel(game->hud.img, i + 10, j + 10, 0x000FF); 
// 				game->hud.dot_img = mlx_texture_to_image(game->mlx, game->hud.w_dot);
// 				if (mlx_image_to_window(game->mlx, game->hud.dot_img, j + game->hud.dot_img->width, i + game->hud.dot_img->height) < 0)
// 					return (error(game, "map draw error", NOSYSERR), false);
// 			}
// 			// else if (game->map.grid[i][j] == '0')
// 			// {
// 			// 	game->hud.dot_img = mlx_texture_to_image(game->mlx, game->hud.b_dot);
// 			// 	if (mlx_image_to_window(game->mlx, game->hud.dot_img, i + 130 , j + 130) < 0)
// 			// 		return (error(game, "map draw error", NOSYSERR), false);
// 			// }
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// void draw_circle(mlx_image_t	*img)
// {
// 	int x;
// 	int y;
// 	int d;
// 	x = 0;
// 	y = MINIMAP_RADIUS;
// 	d = 3 - 2 * MINIMAP_RADIUS;
// 	while (x <= y)
// 	{
// 		mlx_put_pixel(img, MINIMAP_CENTER + x, MINIMAP_CENTER + y, 0xFFFFFF); // Draw points in all octants
// 		mlx_put_pixel(img, MINIMAP_CENTER + x, MINIMAP_CENTER - y, 0xFFFFFF);
// 		mlx_put_pixel(img, MINIMAP_CENTER - x, MINIMAP_CENTER + y, 0xFF0000FF);
// 		mlx_put_pixel(img, MINIMAP_CENTER - x, MINIMAP_CENTER - y, 0xFFFFFF);
// 		mlx_put_pixel(img, MINIMAP_CENTER + y, MINIMAP_CENTER + x, 0xFFFFFF);
// 		mlx_put_pixel(img, MINIMAP_CENTER + y, MINIMAP_CENTER - x, 0xFFFFFF);
// 		mlx_put_pixel(img, MINIMAP_CENTER - y, MINIMAP_CENTER + x, 0xFFFFFF);
// 		mlx_put_pixel(img, MINIMAP_CENTER - y, MINIMAP_CENTER - x, 0xFFFFFF);
// 		if (d < 0)
// 			d = d + 4 * x + 6;
// 		else
// 		{
// 			d = d + 4 * (x - y) + 10;
// 			y--;
// 		}
// 		x++;
// 	}
// }

// bool	check_step(t_game *game, int j, int i)
// {
// 	if (game->hud.map[j][i] == 'E')
// 	{
// 		// if (game->xy.check_coin == game->map.collectibles)
// 		// 	return (write(1, "win!\n", 5), game->pi.key_state = 0);
// 		// else
// 			return (true);
// 	}
// 	if (game->hud.map[j][i] == 'C')
// 	{
// 		// game->xy.check_coin++;
// 		// game->map.map[j][i] = '0';
// 	}
// 	game->hud.map[j][i] = 'N';
// 	game->hud.map[game->ply.pos.y][game->ply.pos.x] = '0';
// 	printf("plyer previous pos:%c at here:{%d,%d}\n", game->hud.map[game->ply.pos.y][game->ply.pos.x], game->ply.pos.y, game->ply.pos.x);
// 	game->ply.pos.x = i;
// 	game->ply.pos.y = j;
// 	draw_minimap(game);
// 	// game->hud.img->instances[1].y += 1;
// 	// draw_minimap(game);
// 	return (true);
// }

// /*This function changes the position of the player in the
// map to shows it as moving.*/
// int	move(t_game *game, int j, int i)
// {
// 	int		x;
// 	int		y;
// 	x = game->ply.pos.x + i;
// 	y = game->ply.pos.y + j;
// 	if (game->hud.map[y][x] != '1')
// 		check_step(game, (y), (x));
// 	return (0);
// }

// void fill_circle(t_game *game)
// {
//     int radius = MINIMAP_RADIUS;
//     int player_x = game->hud.pos.x;
//     int player_y = game->hud.pos.y;
//     int dot_size = DOT_SIZE;
//     for (int dx = -radius; dx <= radius; dx++)
//     {
//         for (int dy = -radius; dy <= radius; dy++)
//         {
//             int x = player_x + dx;
//             int y = player_y + dy;
//             // Check if the point (x, y) is within the circle
//             if (dx*dx + dy*dy <= radius*radius)
//             {
//                 // Check if the point is within the bounds of the map
//                 if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
//                 {
//                     // Calculate the screen coordinates for drawing
//                     int screen_x = (player_x - radius) * dot_size + dx * dot_size;
//                     int screen_y = (player_y - radius) * dot_size + dy * dot_size;
//                     // Check if the map element is a wall
//                     if (game->hud.map[y][x] == '1')
//                     {
//                         // Draw the wall image at the calculated screen coordinates
//                         mlx_image_to_window(game->mlx, game->hud.img_wall, screen_x, screen_y);
//                     }
//                 }
//             }
//         }
//     }
// }

// void fill_circle(t_game *game)
// {
//     int radius = MINIMAP_RADIUS;
//     int player_x = game->hud.pos.x;
//     int player_y = game->hud.pos.y;
//     int dot_size = DOT_SIZE; // Define the size of each image
//     for (int dx = -radius; dx <= radius; dx++)
//     {
//         for (int dy = -radius; dy <= radius; dy++)
//         {
//             int x = player_x + dx * dot_size;
//             int y = player_y + dy * dot_size;
//             // Check if the point (x, y) is within the circle
//             if (dx*dx + dy*dy <= radius*radius)
//             {
//                 // Check if the point is within the bounds of the map
//                 if (x >= 0 && x < 29 * dot_size && y >= 0 && y < 14 * dot_size)
//                 {
//                     // Check if the map element is a wall
//                     if (game->hud.map[y / dot_size][x / dot_size] == '1')
//                     {
//                         // Draw the wall image at the point (x, y)
//                         mlx_image_to_window(game->mlx, game->hud.img_wall, x, y);
//                     }
//                 }
//             }
//         }
//     }
// }

// void fill_circle(t_game *game)
// {
// 	int N = 2* MINIMAP_RADIUS +1;
// 	int x, y;  // Coordinates inside the rectangle
// 	// Draw a square of size N*N.
// 	for (int i = 0; i < N; i++)
// 	{
// 		for (int j = 0; j < N; j++)
// 		{
// 			// Start from the left most corner point
// 			x = i- MINIMAP_RADIUS;
// 			y = j- MINIMAP_RADIUS;
// 			// If this point is inside the ci`cle, print it
// 			if (x*x + y*y < MINIMAP_RADIUS * MINIMAP_RADIUS + 1 )
// 				mlx_put_pixel(game->hud.circle_bck, MINIMAP_CENTER + x, MINIMAP_CENTER + y, 0x000FF); 
// 			// else // If outside the circle, print space
// 			// 	printf(" ");
// 			// printf(" ");
// 		}
// 		// printf("\n");
// 	}
// }

bool draw_minimap(t_game *game)
{
	uint32_t i;
	uint32_t j;
	uint32_t x;
	uint32_t y;

	i = 0;
	while (i < game->map.map_height)
	{
		j = 0;
		while (j <= game->map.widths[i])
		{
			x = j * DOT_SIZE;  // Adjust the position based on the dot size
			y = i * DOT_SIZE;  // Adjust the position based on the dot size
			if (game->hud.map[i][j] == '1')
			{
				if (mlx_image_to_window(game->mlx, game->hud.img_wall, x + DOT_SIZE, y + DOT_SIZE) < 0)
					return (error(game, "map draw error", NOSYSERR), false);
			}
			else if (game->hud.map[i][j] == 'N')
			{
				printf("plyer x:%d and y:%d\n", game->ply.pos.x, game->ply.pos.y);
				if (mlx_image_to_window(game->mlx, game->hud.img_ply, x + DOT_SIZE, y + DOT_SIZE) < 0)
					return (error(game, "map draw error", NOSYSERR), false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

void	move_map(t_game *game, int direction)
{
	size_t	i;
	mlx_image_t	*sample;

	i = 0;
	sample = game->hud.img_wall;
	printf("pos y:%d pos x:%d\n",game->hud.pos.y, game->hud.pos.x);
	if (direction == UP && game->hud.map[game->hud.pos.y - 1][game->hud.pos.x] != '1')
	{
		while (i < sample->count)
			sample->instances[i++].y += DOT_SIZE;
		game->hud.pos.y--;
	}
	if (direction == DOWN && game->hud.map[game->hud.pos.y + 1][game->hud.pos.x] != '1')
	{
		while (i < sample->count)
			sample->instances[i++].y -= DOT_SIZE;
		game->hud.pos.y++;
	}
	if (direction == LEFT && game->hud.map[game->hud.pos.y][game->hud.pos.x + 1] != '1')
	{
		while (i < sample->count)
			sample->instances[i++].x += DOT_SIZE;
		game->hud.pos.x++;
	}
	if (direction == RIGHT && game->hud.map[game->hud.pos.y][game->hud.pos.x - 1] != '1')
	{
		while (i < sample->count)
			sample->instances[i++].x -= DOT_SIZE;
		game->hud.pos.x--;
	}
}
void fill_map_circle(t_game *game);
void	hud_move_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	(void)keydata;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		move_map(game, DOWN);
		// game->hud.img_ply->instances[0].y += DOT_SIZE;
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		// game->hud.img_ply->instances[0].y -= DOT_SIZE;
		move_map(game, UP);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		// game->hud.img_ply->instances[0].x += DOT_SIZE;
		move_map(game, LEFT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		// game->hud.img_ply->instances[0].x -= DOT_SIZE;
		move_map(game, RIGHT);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	// 	game->hud.img_ply->instances[0].x -= DOT_SIZE;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	// fill_map_circle(game);
	
}

// void hud_move_hook(mlx_key_data_t keydata, void* param)
// {
// 	t_game *game = (t_game *)param;
// 	// (void)param;
// 	// If we PRESS the 'J' key, print "Hello".
// 	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
// 		puts("Hello ");
// 	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
// 	{
// 		// printf("x:%d and y:%d\n", game->ply.pos.x, game->ply.pos.y);
// 		move(game, -1, 0);
// 	}
// 	// If we RELEASE the 'K' key, print "World".
// 	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
// 		puts("World");
// 	// If we HOLD the 'L' key, print "!".
// 	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
// 		puts("!");
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 	mlx_close_window(game->mlx);
// }

void draw_circle(t_game *game)
{
	for (int angle = 0; angle < 360; angle++) {
		// Convert angle to radians
		double radians = angle * M_PI / 180.0;

		// Calculate (x, y) coordinates
		int x = 65 + (int)((MINIMAP_RADIUS + 110) * cos(radians));
		int y = 65 + (int)((MINIMAP_RADIUS + 110) * sin(radians));
		// Print the point (x, y)
		mlx_put_pixel(game->hud.circle, 65 + x, 65 + y, 0xFF0000FF); // Draw points in all octants
		// printf("(%d, %d)\n", x, y);
	}
}


void fill_map_circle(t_game *game)
{
    int radius = MINIMAP_RADIUS;
    int player_x = game->hud.pos.x;
    int player_y = game->hud.pos.y;
    int dot_size = DOT_SIZE;
    int window_width = game->mlx->width;
    int window_height = game->mlx->height;

    for (int dx = -radius; dx <= radius; dx++)
    {
        for (int dy = -radius; dy <= radius; dy++)
        {
            int x = player_x + dx;
            int y = player_y + dy;

            // Check if the point (x, y) is within the circle
            if (dx*dx + dy*dy <= radius*radius)
            {
                // Check if the point is within the bounds of the map
                if (x >= 0 && x < 29 && y >= 0 && y < 14)
                {
                    // Calculate the screen coordinates for drawing
                    int screen_x = (window_width / 2) - (radius * dot_size) + (dx * dot_size);
                    int screen_y = (window_height / 2) - (radius * dot_size) + (dy * dot_size);

                    // Check if the calculated screen coordinates are within the window bounds
                    if (screen_x >= 0 && screen_x < window_width && screen_y >= 0 && screen_y < window_height)
                    {
                        // Check if the map element is a wall
                        if (game->hud.map[y][x] == '1')
                        {
                            // Draw the wall image at the calculated screen coordinates
                            mlx_image_to_window(game->mlx, game->hud.img_wall, screen_x - 295, screen_y - 120);
                        }
                        if (game->hud.map[y][x] == 'N')
                        {
                            // Draw the wall image at the calculated screen coordinates
                            mlx_image_to_window(game->mlx, game->hud.img_ply, screen_x - 295, screen_y - 120);
                        }
                    }
                }
            }
        }
    }
}

 void	draw(void *param)
 {
	(void)param;
	return;
 }

bool	mini_map(t_game	*game)
{
	game->hud.map = creat_sample_gird(game);
	game->hud.pos = game->ply.pos;
	game->hud.b_dot = mlx_load_png("./texture/black_8.png");
	game->hud.w_dot = mlx_load_png("./texture/white_8.png");
	game->hud.img_wall = mlx_texture_to_image(game->mlx, game->hud.w_dot);
	game->hud.ply = mlx_load_png("./texture/ply_8.png");
	game->hud.img_ply = mlx_texture_to_image(game->mlx, game->hud.ply);
	// if (!game->hud.w_dot)
	// 	return (error(game,"texture of hud", NOSYSERR), false);
	game->hud.circle_bck = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height); //later on the width and heigh should be changed
	if (!game->hud.circle_bck || mlx_image_to_window(game->mlx, game->hud.circle_bck, 0, 0) < 0)
		return (error(game, "MLX Windows failed!!!",NOSYSERR), false);
	// fill_map_circle(game);
	draw_minimap(game);
	game->hud.circle = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height); //later on the width and heigh should be changed
	if (!game->hud.circle || mlx_image_to_window(game->mlx, game->hud.circle, 0, 0) < 0)
		return (error(game, "MLX Windows failed!!!",NOSYSERR), false);
	draw_circle(game);
	mlx_key_hook(game->mlx, &hud_move_hook, game);

	// mlx_put_pixel(game->scn.img, 100, 100, 0xFF0000FF);
	return(true);
}

bool	mlx_initiate(t_game	*game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!game->mlx)
		return(error(game, "MLX is not initiated!!!", NOSYSERR), false);
	game->scn.img = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	if (!game->scn.img || (mlx_image_to_window(game->mlx, game->scn.img, 0, 0) < 0))
		return (error(game, "MLX Windows failed!!!",NOSYSERR), false);
	return (true);
}
	// mlx_put_pixel(game->scn.img, 100, 100, 0xFF0000FF);
