/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:28:33 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/03/03 18:32:35 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../include/cub_3d.h"

typedef struct s_game t_game;
typedef struct s_parse t_parse;
typedef struct s_map t_map;

/**************init_free_funcs.c***************/

void	initiate_game(t_game *game, char *file);
void	initiate_map(t_map *map);
void	initiate_parser(t_parse *parser, t_game *game, char *file);
void	free_array(char **map);
void	free_parser(t_parse *parser);
void	close_game(t_game *game);


/**************errors_handling.c***************/

char    *error_table(char *code);
int     finish(t_game *game, char *msg, int no);


/**************print_map_details.c***************/
void print_map_details(t_game *game);

#endif
