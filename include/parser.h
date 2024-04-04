/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:46:15 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/04/04 01:26:38 by flafi            ###   ########.fr       */
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

bool					trim_line(t_parse *parser);
int						fetch_map_detail(t_game *game);
int						parsing_map(t_game *game);
int						check_map_file_format_add(t_game *game, char *file);
int						checking_map(int ac, char **av, t_game *game);
/*****************checking_map_path.c********************/

void					print_gird(char **grid);
char					**creat_sample_gird(t_game *game);
bool					fill_grid(t_game *game, t_pos pos, char **grid);
int						check_map_path(t_game *game);
int						fetch_map_detail(t_game *game);
int						assessment_png_file(t_game *game);
bool					line_is_empty(char *line);
bool					check_element(t_parse *parser);
int						read_element(t_parse *parser);
bool					assessment_map(t_game *game);
bool					assessment_element(t_game *game, int err);
int						read_map(t_game *game);
char					**rm_empty_array_elements(char **str_array);
size_t					array_length(char **array);
int						check_digit(char *color);
void					str_trim(char *str, char ch);
int						check_map_char(t_game *game);
int						calc_map_rows_widths(t_map *map);
bool					check_texture_file_path(char *path);
bool					all_chr_present(char *s1, const char *s2);
uint32_t				*ft_realloc_int(uint32_t *input, size_t old_count,
							size_t new_count);
char					**ft_realloc_strings(char **ptr, size_t old_count,
							size_t new_count);
#endif
