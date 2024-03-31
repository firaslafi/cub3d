/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:17:56 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/03/03 18:32:35 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"


	/*Just to know: EXIT_FAILURE is a constant defined in the stdlib.h
	header file that has a value of -1. This exit code is typically used
	to indicate a more specific type of error, 
	such as a file I/O error or a memory allocation error.*/
int	finish(t_game *game, char *msg, int type)
{
	if (type == NOSYSERR)
	{
		ft_putstr_fd("\033[38;5;214mHiii\033[0m, there is an error:--> "RED, 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n"RESET, 2);
		// ft_putstr_fd(error_table(error), 2);
	}
	if (type == SYSERR)
	{
		strerror(errno);
		perror("The system error is\033[38;5;196m");
	}
	if (type == MSG)
	{
		ft_putstr_fd("\033[38;5;214mHiii\033[0m, "RED, 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n"RESET, 2);
	}
	close_game(game);
	// system("leaks ./cub3D");
	return (exit(EXIT_FAILURE), 1);
}
