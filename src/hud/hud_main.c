

#include "../include/hud.h"

bool draw_minimap(t_game *game)
{
	uint32_t i;
	uint32_t j;
	uint32_t x;
	uint32_t y;
	printf("hiiii\n");
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
				// if (mlx_image_to_window(game->mlx, game->hud.img_wall, x + DOT_SIZE, y + DOT_SIZE) < 0)
				// 	return (finish(game, "map draw error", NOSYSERR), false);
				mlx_put_pixel(game->hud.img_wall, x + DOT_SIZE, y + DOT_SIZE, 0x005C4033);
			}
			// else if (game->hud.map[i][j] == 'N')
			else if (ft_strchr("NEWS", game->hud.map[i][j]))
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

// void	mlx_key(mlx_key_data_t keydata, void *param)
// {
// 	t_game	*game;

// 	game = param;
// 	(void)keydata;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
// 		move_player(game, DOWN);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
// 		move_player(game, UP);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 		move_player(game, LEFT);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 		move_player(game, RIGHT);
// 	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 		finish(game, "Project finished.", MSG);
// }

void pad_map_lines(char **map, uint32_t map_height, uint32_t longest_line, uint32_t *line_lengths) {
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
	// pad_map_lines(game->hud.map, game->map.map_height, game->map.max_width, game->map.widths);
	for(uint32_t i = 0; i < game->map.map_height; i++)
		printf("line[%d]:	|%s|\n", i, game->hud.map[i]);
	game->hud.pos = game->ply.pos;
	// mlx_delete_image(game->mlx, game->hud.img);	// delete the image
	game->hud.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_WIDTH);	// create new image
	// mlx_image_to_window(game->mlx, game->hud.img, 0, 0);
	game->hud.w_dot = mlx_load_png("./texture/white_8.png");
	game->hud.img_wall = mlx_texture_to_image(game->mlx, game->hud.w_dot);
	game->hud.ply = mlx_load_png("./texture/ply_8.png");
	game->hud.img_ply = mlx_texture_to_image(game->mlx, game->hud.ply);
	// draw_minimap(game);
	return(true);
}

// bool	mlx_initiate(t_game	*game)
// {
// 	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
// 	if (!game->mlx)
// 		return(finish(game, "MLX is not initiated!!!", NOSYSERR), false);
// 	game->scn.img = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
// 	if (!game->scn.img || (mlx_image_to_window(game->mlx, game->scn.img, 0, 0) < 0))
// 		return (finish(game, "MLX Windows failed!!!",NOSYSERR), false);
// 	return (true);
// }
	// mlx_put_pixel(game->scn.img, 100, 100, 0xFF0000FF);
