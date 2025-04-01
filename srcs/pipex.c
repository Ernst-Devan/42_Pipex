/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:11:03 by dernst            #+#    #+#             */
/*   Updated: 2025/04/01 15:03:54 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include <sys/wait.h>
#include "pipex.h"
#include <errno.h>

void	manage_first_command(t_fd fd, int *pipefd, t_args args)
{
	close(pipefd[0]);
	if (dup2(fd.fd_in, STDIN_FILENO) < 0)
		exit_free(args, 1, fd, pipefd);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		exit_free(args, 1, fd, pipefd);
	close(fd.fd_in);
	close(fd.fd_out);
	close(pipefd[1]);
	if (args.command1)
		execve(args.command1, args.arg1, NULL);
}

void	manage_second_command(t_fd fd, int *pipefd, t_args args)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		exit_free(args, 1, fd, pipefd);
	if (dup2(fd.fd_out, STDOUT_FILENO) < 0)
		exit_free(args, 1, fd, pipefd);
	close(pipefd[0]);
	close(fd.fd_in);
	close(fd.fd_out);
	execve(args.command2, args.arg2, NULL);
}

void	pipex(t_args args, t_fd fd, int *pipefd, int fd_error)
{
	int	pid1;
	int	pid2;
	int	status;

	pid1 = fork();
	if (pid1 == 0)
		manage_first_command(fd, pipefd, args);
	else if (pid1 < 0)
		exit_free(args, EAGAIN, fd, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		manage_second_command(fd, pipefd, args);
	else if (pid2 < 0)
		exit_free(args, EAGAIN, fd, pipefd);
	close_fd(fd, pipefd);
	while (wait(&status) != -1)
		continue ;
	if (fd_error == 1)
		exit_free(args, 1, fd, pipefd);
	exit_free(args, WEXITSTATUS(status), fd, pipefd);
}

int	main(int ac, char **av, char **env)
{
	t_args	args;
	t_fd	fd;
	int		fd_error;
	int		pipefd[2];

	if (ac != 5)
		return (1);
	fd_error = 0;
	fd = init_fd(av, &fd_error);
	args = parsing(av, get_env_path(env), fd, pipefd);
	pipex(args, fd, pipefd, fd_error);
}
