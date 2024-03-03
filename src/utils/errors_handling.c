/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:17:56 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/19 21:42:57 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*error_table(char *code)
{
	int		i;
	char	*table[18];

	i = 0;
	table[0] = "INPUT\033[38;5;196mAmount of input is wrong.\033[0m\n";
	table[1] = "MAFOR\033[38;5;196mMap file formant is wrong.\033[0m\n";
	table[2] = "MAROW\033[38;5;196mMap structure is wrong.\033[0m\n";
	table[3] = "MPADD\033[38;5;196mMap file address has problem.\033[0m\n";
	table[16] = "MTFAR\033[38;5;196mMap texture file has problem.\033[0m\n";
	table[17] = "MCCIW\033[38;5;196mMap ceiling color wrong.\033[0m\n";
	table[4] = "MFCIW\033[38;5;196mMap floor color wrong.\033[0m\n";
	table[5] = "MALSW\033[38;5;196mMap lines are not in the same size.\033[0m\n";
	table[6] = "MAEPW\033[38;5;196mExit/Player/collectable is wrong!\033[0m\n";
	table[7] = "MACWR\033[38;5;196mWrong charactor in map.\033[0m\n";
	table[8] = "MALOC\033[38;5;196musing malloc failed.\033[0m\n";
	table[9] = "MAWRG\033[38;5;196mMap path is not correct.\033[0m\n";
	table[10] = "XPMWA\033[38;5;196mWall xpm file is incorrect.\033[0m\n";
	table[11] = "XPMEX\033[38;5;196mExit xpm file is incorrect.\033[0m\n";
	table[12] = "XPMCO\033[38;5;196mCoin xpm file is incorrect..\033[0m\n";
	table[13] = "XPMPL\033[38;5;196mplayer xpm file is incorrect..\033[0m\n";
	table[14] = "MLXIN\033[38;5;196mMlx initiation error.\033[0m\n";
	table[15] = "MLXWI\033[38;5;196mMlx creat new windows error.\033[0m\n";
	while (ft_strncmp(table[i], code, 5) != 0)
		i++;
	return ((table[i] + 5));
}

	/*Just to know: EXIT_FAILURE is a constant defined in the stdlib.h
	header file that has a value of -1. This exit code is typically used
	to indicate a more specific type of error, 
	such as a file I/O error or a memory allocation error.*/
int	error(t_game *game, char *error, int no)
{
	if (no == NOSYSERR)
	{
		ft_putstr_fd("\033[38;5;214mHiii\033[0m, there is an error:--> "RED, 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n"RESET, 2);
		// ft_putstr_fd(error_table(error), 2);
	}
	if (no == SYSERR)
	{
		strerror(errno);
		perror("The system error is\033[38;5;196m");
	}
	close_game(game);
	// system("leaks ./cub3D");
	return (exit(EXIT_FAILURE), 1);
}
