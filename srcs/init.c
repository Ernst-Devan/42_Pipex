/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:59:40 by dernst            #+#    #+#             */
/*   Updated: 2025/03/27 10:23:31 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "fcntl.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

t_args init_arg()
{
	t_args args;
	
	args.arg1 = NULL;
	args.arg2 = NULL;
	args.command1 = NULL;
	args.command2 = NULL;
	return (args);
}

t_fd	init_fd(char **av)
{
	t_fd	fd;

	fd.fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd.fd_out < 0 || access(av[4], W_OK))
		exit(EBADF);
	fd.fd_in = open(av[1], O_RDONLY);
	return (fd);
}