/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:37:54 by dernst            #+#    #+#             */
/*   Updated: 2025/03/31 16:14:29 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_args
{
	char	**arg1;
	char	*command1;
	char	**arg2;
	char	*command2;
}	t_args;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
}	t_fd;

// Errors.c
void	exit_free(t_args args, int error, t_fd fd, int *pipefd);
void	cleanup_split(char **splited_str);
void	close_fd(t_fd fd, int *pipefd);

// Init.c
t_args	init_arg(void);
t_fd	init_fd(char **av, int *fd_error);

// Parsing.c
t_args	parsing(char **argv, char *path, t_fd fd, int *pipefd);
char	**parse_env(char *path);
char	*get_env_path(char **env);

#endif