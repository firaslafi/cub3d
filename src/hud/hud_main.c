

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
				if (mlx_image_to_window(game->mlx, game->hud.img_wall, x + DOT_SIZE, y + DOT_SIZE) < 0)
					return (finish(game, "map draw error", NOSYSERR), false);
			}
			else if (game->hud.map[i][j] == 'N')
			// else if (ft_strchr("NEWS", game->hud.map[i][j]))
			{
				//printf("plyer x:%d and y:%d\n", game->ply.pos.x, game->ply.pos.y);
				if (mlx_image_to_window(game->mlx, game->hud.img_ply, x + DOT_SIZE, y + DOT_SIZE) < 0)
					return (finish(game, "map draw error", NOSYSERR), false);
			}
		}
	}
	return (true);
}

void	move_minimap_player(t_game *game, int direction)
{
	t_hud	*sample;

	sample = &game->hud;
	if (game->ply.u_d == 1 && direction == UP && sample->map[sample->pos->y - 1][sample->pos->x] != '1')
	{
		sample->img_ply->instances[0].y -= DOT_SIZE;
		sample->pos->y--;
	}
	if (game->ply.u_d == -1 &&direction == DOWN && sample->map[(*sample->pos).y + 1][(*sample->pos).x] != '1')
	{
		sample->img_ply->instances[0].y += DOT_SIZE;
		sample->pos->y++;
	}
	if (game->ply.l_r == -1 &&direction == LEFT && sample->map[sample->pos->y][sample->pos->x - 1] != '1')
	{
		sample->img_ply->instances[0].x -= DOT_SIZE;
		sample->pos->x--;
	}
	if (game->ply.l_r == 1 &&direction == RIGHT && sample->map[sample->pos->y][sample->pos->x + 1] != '1')
	{
		sample->img_ply->instances[0].x += DOT_SIZE;
		sample->pos->x++;
	}
}

void	mlx_minimap_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	(void)keydata;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_minimap_player(game, UP);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_minimap_player(game, DOWN);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_minimap_player(game, RIGHT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_minimap_player(game, LEFT);
	// if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// 	finish(game, "Project finished.", MSG);
}

void pad_map_lines(char **map, uint32_t map_height, uint32_t longest_line, uint32_t *line_lengths)
{
	size_t	i;
	size_t	j;
	size_t	current_length;
	size_t	spaces_needed;
	char 	*padded_line;

	i = -1;
	while (++i < map_height)
	{
		current_length = line_lengths[i];
		spaces_needed = longest_line - current_length;
		padded_line = malloc((current_length + spaces_needed + 1) * sizeof(char));
		if (padded_line == NULL)
			return;
		ft_strlcpy(padded_line, map[i], ft_strlen(map[i]) + 1);
		j = current_length;
		while (j < current_length + spaces_needed)
			padded_line[j++] = ' ';
		padded_line[current_length + spaces_needed] = '\0';
		free(map[i]);
		map[i] = padded_line;
		line_lengths[i] = longest_line;
		// i++;
	}
}

bool	mini_map(t_game	*game)
{
	game->hud.map = creat_sample_gird(game);
	for(uint32_t i = 0; i < game->map.map_height; i++)
		printf("line[%d]:	|%s|\n", i, game->hud.map[i]);
	game->hud.pos = &game->ply.pos;
	game->hud.w_dot = mlx_load_png("./texture/white_8.png");
	game->hud.img_wall = mlx_texture_to_image(game->mlx, game->hud.w_dot);
	game->hud.ply = mlx_load_png("./texture/ply_8.png");
	game->hud.img_ply = mlx_texture_to_image(game->mlx, game->hud.ply);
	draw_minimap(game);
	return(true);
}
