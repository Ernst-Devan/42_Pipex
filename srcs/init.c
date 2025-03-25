/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:59:40 by dernst            #+#    #+#             */
/*   Updated: 2025/03/25 16:13:57 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "fcntl.h"

t_fd	init_fd(char **av)
{
	t_fd	fd;

	fd.fd_in = open(av[1], O_RDONLY);
	fd.fd_out = open(av[4], O_CREAT | O_WRONLY);
	return (fd);
}