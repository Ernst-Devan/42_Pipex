/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:25:44 by dernst            #+#    #+#             */
/*   Updated: 2025/03/27 10:25:40 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>


t_args	parsing(char **argv)
{
	t_args args;
	char *temp;

	args = init_arg();
	
	args.arg1 = ft_split(argv[2], ' ');
	if (!args.arg1)
		exit_free(args, ENOMEM);
	temp = ft_strjoin("/bin/", args.arg1[0]);
	args.command1 = temp;
	if (!args.command1)
		exit_free(args, ENOMEM);
	args.arg2 = ft_split(argv[3], ' ');
	if (!args.arg2)
		exit_free(args, ENOMEM);
	temp = ft_strjoin("/bin/", args.arg2[0]);
	args.command2 = temp;
	if (!args.command2)
		exit_free(args, ENOMEM);
	if (access(args.command1, X_OK) != 0)
		exit_free(args, 1);
	if (access(args.command2, X_OK) != 0)
		exit_free(args, 1);
	return (args);
}
