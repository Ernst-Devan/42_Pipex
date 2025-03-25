/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:25:44 by dernst            #+#    #+#             */
/*   Updated: 2025/03/25 15:45:05 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"

t_args	parsing(char **argv)
{
	t_args args;

	//! Return error if malloc of split fails
	args.arg1 = ft_split(argv[2], ' ');
	args.command1 = ft_strdup(args.arg1[0]);
	args.arg2 = ft_split(argv[3], ' ');
	args.command2 = ft_strdup(args.arg2[0]);
	return (args);
}
