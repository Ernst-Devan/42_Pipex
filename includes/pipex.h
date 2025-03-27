/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:37:54 by dernst            #+#    #+#             */
/*   Updated: 2025/03/26 15:05:28 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PIPEX_H_
# define _PIPEX_H_

typedef struct s_args
{
	char **arg1;
	char *command1;
	char **arg2;
	char *command2;
}	t_args;

typedef struct s_fd
{
	int fd_in;
	int fd_out;
}	t_fd;

t_args 	init_arg();
t_fd	init_fd(char **av);
t_args	parsing(char **argv);
void	exit_free(t_args args, int error);

#endif