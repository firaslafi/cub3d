/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:46:15 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/20 19:35:32 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../include/cub_3d.h"

# define WHITSPACE " \t\n\f\v\r"
# define MAPCHRS "NEWS10D "

typedef struct s_map	t_map;
typedef struct s_game	t_game;
typedef struct s_pos	t_pos;
typedef struct s_parse	t_parse;

/*****************checking_format.c********************/

bool	trim_line(t_parse *parser);
int		fetch_map_detail(t_game *game);
int		parsing_map(t_game *game);
int		check_map_file_format_add(t_game *game, char *file);
int		checking_map(int ac, char **av, t_game *game);

/*****************checking_map_path.c********************/

void	print_gird(char **grid);
char	**creat_sample_gird(t_game *game);
bool	fill_grid(t_game *game, t_pos pos, char **grid);
int		check_map_path(t_game *game);

#endif
