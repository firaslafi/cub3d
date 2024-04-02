/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:46:15 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/04/03 00:48:49 by flafi            ###   ########.fr       */
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
