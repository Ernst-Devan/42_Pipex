/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:22:50 by dernst            #+#    #+#             */
/*   Updated: 2025/03/26 15:05:58 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"
#include "libft.h"

//! echo $? To check the good return 126 (Pipe fails for exemple) search online
//! Ft_split not in norm

void	exit_free(t_args args, int error)
{
	int	i;

	i = 0;
	if (args.arg1)
	{
		while (args.arg1[i])
		{
			free(args.arg1[i]);
			i++;
		}
		free(args.arg1);
	}
	i = 0;
	if (args.arg2)
	{
		while (args.arg2[i])
			{
				free(args.arg2[i]);
				i++;
			}
	}
		free(args.arg2);
	if (args.command1)
		free(args.command1);
	if (args.command2)
		free(args.command2);
	exit(error);
}
