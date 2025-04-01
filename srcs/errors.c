/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:22:50 by dernst            #+#    #+#             */
/*   Updated: 2025/04/01 15:13:55 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"
#include "libft.h"

void	cleanup_split(char **splited_str)
{
	int	i;

	i = 0;
	if (splited_str)
	{
		while (splited_str[i] != NULL)
		{
			free(splited_str[i]);
			i++;
		}
		if (splited_str)
			free(splited_str);
	}
}

void	close_fd(t_fd fd, int *pipefd)
{
	if (fd.fd_in)
		close(fd.fd_in);
	if (fd.fd_out)
		close(fd.fd_out);
	if (pipefd[0])
		close(pipefd[0]);
	if (pipefd[1])
		close(pipefd[1]);
}

void	exit_free(t_args args, int error, t_fd fd, int *pipefd)
{
	close_fd(fd, pipefd);
	if (args.arg1)
		if (args.command1 != args.arg1[0])
			free(args.command1);
	if (args.arg2)
		if (args.command2 != args.arg2[0])
			free(args.command2);
	cleanup_split(args.arg1);
	cleanup_split(args.arg2);
	exit(error);
}
