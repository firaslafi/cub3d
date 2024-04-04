/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:42:15 by flafi             #+#    #+#             */
/*   Updated: 2024/04/04 01:48:33 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hud.h"

void	pad_map_lines(char **map, uint32_t map_height, uint32_t longest_line,
		uint32_t *line_lengths)
{
	size_t	i;
	size_t	current_length;
	size_t	spaces_needed;
	char	*padded_line;
	size_t	j;

	i = 0;
	while (i < map_height)
	{
		current_length = line_lengths[i];
		spaces_needed = longest_line - current_length;
		padded_line = malloc((current_length + spaces_needed + 1)
				* sizeof(char));
		strcpy(padded_line, map[i]);
		j = current_length;
		while (j < current_length + spaces_needed)
		{
			padded_line[j] = ' ';
			j++;
		}
		padded_line[current_length + spaces_needed] = '\0';
		free(map[i]);
		map[i] = padded_line;
		line_lengths[i++] = longest_line;
	}
}
