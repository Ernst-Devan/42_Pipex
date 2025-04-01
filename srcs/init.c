/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:59:40 by dernst            #+#    #+#             */
/*   Updated: 2025/03/31 17:34:34 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "fcntl.h"
#include <libft.h>

t_args	init_arg(void)
{
	t_args	args;

	args.arg1 = NULL;
	args.arg2 = NULL;
	args.command1 = NULL;
	args.command2 = NULL;
	return (args);
}

t_fd	init_fd(char **av, int *fd_error)
{
	t_fd	fd;

	fd.fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd.fd_out < 0)
		*fd_error = 1;
	fd.fd_in = open(av[1], O_RDONLY);
	return (fd);
}
