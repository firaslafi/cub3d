/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:36 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/04/04 01:02:57 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

size_t	array_length(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL || !*array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

bool	all_chr_present(char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				break ;
			j++;
		}
		if (s1[i] != s2[j])
			return (false);
		i++;
	}
	return (true);
}

/* This function reallocate an array of string from its old size to its
 new size.*/
uint32_t	*ft_realloc_int(uint32_t *input, size_t old_count, size_t new_count)
{
	uint32_t	*new_ptr;
	size_t		i;

	if (!input)
	{
		new_ptr = (uint32_t *)ft_calloc(new_count + 1, sizeof(uint32_t));
		if (!new_ptr)
			return (NULL);
		return (new_ptr);
	}
	new_ptr = (uint32_t *)ft_calloc(new_count + 1, sizeof(uint32_t));
	if (!new_ptr)
		return (free(input), NULL);
	i = -1;
	while (++i < old_count)
		new_ptr[i] = input[i];
	free(input);
	return (new_ptr);
}

char	**ft_realloc_strings(char **ptr, size_t old_count, size_t new_count)
{
	char	**new_ptr;
	size_t	i;

	if (!ptr)
	{
		new_ptr = (char **) ft_calloc(new_count + 1, sizeof(char *));
		if (!new_ptr)
			return (free_array(new_ptr), NULL);
		return (new_ptr);
	}
	new_ptr = ft_calloc(old_count + new_count + 1, sizeof(char *));
	if (new_ptr == NULL)
		return (free_array(ptr), NULL);
	i = -1;
	while (++i < old_count)
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		if (new_ptr[i] == NULL)
			return (free_array(new_ptr), NULL);
	}
	free_array(ptr);
	return (new_ptr);
}

size_t	list_len(uint32_t *arr)
{
	size_t	count;

	count = 0;
	while (arr && *arr)
	{
		count++;
		arr++;
	}
	return (count);
}
