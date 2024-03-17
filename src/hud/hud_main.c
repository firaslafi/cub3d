

#include "../include/hud.h"
void fill_map_circle(t_game *game);

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

void draw_circle(t_game *game, int offset)
{
	int	angle;

	angle = -1;
	while (++angle < 360)
	{
		// Convert angle to radians
		double radians = angle * M_PI / 180.0;
		// Calculate (x, y) coordinates
		int x = 65 + (int)((MINIMAP_RADIUS + offset) * cos(radians));
		int y = 65 + (int)((MINIMAP_RADIUS + offset) * sin(radians));
		// Print the point (x, y)
		mlx_put_pixel(game->hud.circle, 65 + x, 65 + y, 0xFF0000FF); // Draw points in all octants
	}
}

void fill_circle(t_game *game)
{
	int N = 2* MINIMAP_RADIUS + 130;
	int x, y;  // Coordinates inside the rectangle
	// Draw a square of size N*N.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// Start from the left most corner point
			x = i- MINIMAP_RADIUS;
			y = j- MINIMAP_RADIUS;
			// If this point is inside the ci`cle, print it
			if (x*x + y*y < MINIMAP_RADIUS * MINIMAP_RADIUS + 110)
				mlx_put_pixel(game->hud.circle_bck, MINIMAP_CENTER + x, MINIMAP_CENTER + y, 0x000FF); 
		}
	}
}

bool draw_minimap(t_game *game)
{
	uint32_t i;
	uint32_t j;
	uint32_t x;
	uint32_t y;

	i = -1;
	while (++i < game->map.map_height)
	{
		j = -1;
		while (++j <= game->map.widths[i])
		{
			x = j * DOT_SIZE;  // Adjust the position based on the dot size
			y = i * DOT_SIZE;  // Adjust the position based on the dot size
			if (game->hud.map[i][j] == '1')
			{
				if (mlx_image_to_window(game->mlx, game->hud.img_wall, x + DOT_SIZE, y + DOT_SIZE) < 0)
					return (finish(game, "map draw error", NOSYSERR), false);
			}
			else if (game->hud.map[i][j] == 'N')
			{
				//printf("plyer x:%d and y:%d\n", game->ply.pos.x, game->ply.pos.y);
				if (mlx_image_to_window(game->mlx, game->hud.img_ply, x + DOT_SIZE, y + DOT_SIZE) < 0)
					return (finish(game, "map draw error", NOSYSERR), false);
			}
		}
	}
	return (true);
}

// void	move_player(t_game *game, int direction)
// {
// 	t_hud	*sample;

// 	sample = &game->hud;
// 	// printf("pos y:%d pos x:%d\n",sample->pos.y, sample->pos.x);
// 	if (direction == UP && sample->map[sample->pos.y - 1][sample->pos.x] != '1')
// 	{
// 		sample->img_ply->instances[0].y -= DOT_SIZE;
// 		sample->pos.y--;
// 	}
// 	if (direction == DOWN && sample->map[sample->pos.y + 1][sample->pos.x] != '1')
// 	{
// 		sample->img_ply->instances[0].y += DOT_SIZE;
// 		sample->pos.y++;
// 	}
// 	if (direction == LEFT && sample->map[sample->pos.y][sample->pos.x - 1] != '1')
// 	{
// 		sample->img_ply->instances[0].x -= DOT_SIZE;
// 		sample->pos.x--;
// 	}
// 	if (direction == RIGHT && sample->map[sample->pos.y][sample->pos.x + 1] != '1')
// 	{
// 		sample->img_ply->instances[0].x += DOT_SIZE;
// 		sample->pos.x++;
// 	}
// }

void	clear_instnace(mlx_image_t *sample, int state)
{
	size_t	i;

	i = 0;
	while (i < sample->count)
		sample->instances[i++].enabled = state;
}

void	move_map(t_game *game, int direction)
{
	// size_t	i;
	mlx_image_t	*sample;

	// i = 0;
	sample = game->hud.img_wall;
	// printf("pos y:%d pos x:%d\n",game->hud.pos.y, game->hud.pos.x);
		clear_instnace(sample, false);
	if (direction == UP && game->hud.map[game->hud.pos.y - 1][game->hud.pos.x] != '1')
	{
		// while (i < sample->count)
		// {
		// 	sample->instances[i++].y += DOT_SIZE;
		// }
		game->hud.pos.y--;
		// clear_instnace(sample, true);
			// sample->instances->enabled = true;
	}
	if (direction == DOWN && game->hud.map[game->hud.pos.y + 1][game->hud.pos.x] != '1')
	{
		// while (i < sample->count)
		// 	sample->instances[i++].y -= DOT_SIZE;
		game->hud.pos.y++;
	}
	if (direction == RIGHT && game->hud.map[game->hud.pos.y][game->hud.pos.x + 1] != '1')
	{
		// while (i < sample->count)
		// 	sample->instances[i++].x -= DOT_SIZE;
		game->hud.pos.x++;
	}
	if (direction == LEFT && game->hud.map[game->hud.pos.y][game->hud.pos.x - 1] != '1')
	{
		// while (i < sample->count)
		// 	sample->instances[i++].x += DOT_SIZE;
		game->hud.pos.x--;
	}
	fill_map_circle(game);
}

// void	mlx_key(mlx_key_data_t keydata, void *param)
// {
// 	t_game	*game;

// 	game = param;
// 	(void)keydata;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
// 		// move_player(game, DOWN);
// 		move_map(game, DOWN);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
// 		// move_player(game, UP);
// 		move_map(game, UP);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 		move_map(game, LEFT);
// 		// move_player(game, LEFT);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 		move_map(game, RIGHT);
// 		// move_player(game, RIGHT);
// 	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 		finish(game, "Project finished.", MSG);
// }

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
            uint32_t x = player_x + dx;
            uint32_t y = player_y + dy;

            // Check if the point (x, y) is within the circle
            if (dx*dx + dy*dy <= (radius*radius) + 26)
            {
                // printf("ply x:%d ply y:%d witdth:%d dx:%d dy:%d\n", game->hud.pos.x, game->hud.pos.y, game->map.widths[game->hud.pos.y], dx, dy);// Check if the point is within the bounds of the map
                if (x < game->map.widths[game->hud.pos.y] && y < game->map.map_height)
                {
                    // Calculate the screen coordinates for drawing
                    int screen_x = (radius * dot_size) + (dx * dot_size) + 26;
					int screen_y = (radius * dot_size) + (dy * dot_size) + 26;
                    // int screen_x = (window_width / 2) - (radius * dot_size) + (dx * dot_size);
                    // int screen_y = (window_height / 2) - (radius * dot_size) + (dy * dot_size);

                    // Check if the calculated screen coordinates are within the window bounds
                    if (screen_x >= 0 && screen_x < window_width && screen_y >= 0 && screen_y < window_height)
                    {
                        // Check if the map element is a wall
                        if (x <= game->map.widths[game->hud.pos.y] && game->hud.map[y][x] == '1')
                        {
							// game->hud.img_wall->instances->enabled = true;
							// Draw the wall image at the calculated screen coordinates
							// printf("hi\n");
                            mlx_image_to_window(game->mlx, game->hud.img_wall, screen_x, screen_y);
                        }
                        if (game->hud.map[y][x] == 'N' && !game->hud.ply_flag)
                        {
							clear_instnace(game->hud.img_ply, false);
							game->hud.ply_flag = 1;
                            // Draw the wall image at the calculated screen coordinates
							// clear_instnace(game->hud.img_ply, false);
                            mlx_image_to_window(game->mlx, game->hud.img_ply, screen_x, screen_y);

                        }
                    }
                }
            }
        } 
    }
}

void pad_lines(char **map, uint32_t map_height, uint32_t longest_line, uint32_t *line_lengths) {
    // Iterate over each line of the map
    for (size_t i = 0; i < map_height; i++) {
        size_t current_length = line_lengths[i];

        // Calculate the number of spaces needed to pad the line
        size_t spaces_needed = longest_line - current_length;

        // Allocate memory for the new padded line
        char *padded_line = malloc((current_length + spaces_needed + 1) * sizeof(char));

        // Copy the original line to the padded line
        strcpy(padded_line, map[i]);

        // Append spaces to the padded line
        for (size_t j = current_length; j < current_length + spaces_needed; j++) {
            padded_line[j] = ' ';
        }

        // Add null terminator
        padded_line[current_length + spaces_needed] = '\0';

        // Free the original line
        free(map[i]);

        // Assign the padded line to the map
        map[i] = padded_line;

        // Update the line length
        line_lengths[i] = longest_line;
    }
}

bool	mini_map(t_game	*game)
{
	game->hud.map = creat_sample_gird(game);
	pad_lines(game->hud.map, game->map.map_height, game->map.max_width, game->map.widths);
	for(uint32_t i = 0; i < game->map.map_height; i++)
		printf(GREEN"line[%d]: length:[%zu]"RESET RED"	|%s|\n"RESET, i, ft_strlen(game->hud.map[i]), game->hud.map[i]);
	game->hud.pos = game->ply.pos;
	game->hud.b_dot = mlx_load_png("./texture/black_8.png");
	game->hud.w_dot = mlx_load_png("./texture/white_8.png");
	game->hud.img_wall = mlx_texture_to_image(game->mlx, game->hud.w_dot);
	game->hud.ply = mlx_load_png("./texture/ply_8.png");
	game->hud.img_ply = mlx_texture_to_image(game->mlx, game->hud.ply);
	game->hud.circle_bck = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height); //later on the width and heigh should be changed
	if (!game->hud.circle_bck || mlx_image_to_window(game->mlx, game->hud.circle_bck, 0, 0) < 0)
		return (finish(game, "MLX Windows failed!!!",NOSYSERR), false);
	// fill_circle(game);
	fill_map_circle(game);
	// draw_minimap(game);
	game->hud.circle = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height); //later on the width and heigh should be changed
	if (!game->hud.circle || mlx_image_to_window(game->mlx, game->hud.circle, 0, 0) < 0)
		return (finish(game, "MLX Windows failed!!!",NOSYSERR), false);
	draw_circle(game, 110);
	// draw_circle(game, 109);
	// draw_circle(game, 111);
	// mlx_put_pixel(game->scn.img, 100, 100, 0xFF0000FF);
	return(true);
}

// bool	mlx_initiate(t_game	*game)
// {
	// game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	// if (!game->mlx)
	// 	return(finish(game, "MLX is not initiated!!!", NOSYSERR), false);
	// game->scn.img = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	// // if (!game->scn.img || (mlx_image_to_window(game->mlx, game->scn.img, 0, 0) < 0))
	// if (!game->scn.img)
	// 	return (finish(game, "MLX Windows failed!!!",NOSYSERR), false);
// 	return (true);
// }
	// mlx_put_pixel(game->scn.img, 100, 100, 0xFF0000FF);
