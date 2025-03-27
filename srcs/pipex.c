/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:11:03 by dernst            #+#    #+#             */
/*   Updated: 2025/03/27 10:51:30 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//! Segfault when args are empty if command are empty we need to insert the content of file 1 inside output file
//! echo $? To check the good return 126 (Pipe fails for exemple) search online

#include "libft.h"
#include "unistd.h"
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include <errno.h>

void	manage_parent(int *status)
{
	int	end_pid;

	end_pid = 0;
	while (1)
	{
		end_pid = waitpid(end_pid, status, 0);
		ft_printf("%d \n", end_pid);
		if (end_pid < 0)
			break ;
	}
}
int	 *manage_child(t_fd fd, int *pipefd, t_args args, int index, int *status)
{
	if (index == 0)
	{
		if (dup2(fd.fd_in, STDIN_FILENO) < 0)
			exit_free(args, 1);
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			exit_free(args, 1);
		close(fd.fd_in);
		execve(args.command1, args.arg1, NULL);
	}
	else
	{
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
			exit_free(args, 1);
		if (dup2(fd.fd_out, STDOUT_FILENO) < 0)
			exit_free(args, 1);
		execve(args.command2, args.arg2, NULL);
		
	}
	*status = ENOENT;
	return (status);
}

void	manage_fork(t_fd fd, int *pipefd, t_args args, int index, int *status)
{
	int	pid;
	
	pid = fork();
	if (pid < 0)
		exit_free(args, EAGAIN);
	else if (pid == 0)
		manage_child(fd, pipefd, args, index, status);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_fd	fd;
	int		index;
	int		pipefd[2];
	int		status;

	if (ac != 5)
		return (1);
	fd = init_fd(av);
	args = parsing(av);
	status = 0;
	if (pipe(pipefd) < 0)
		exit_free(args, EPIPE);
	index = 0;
	manage_fork(fd, pipefd, args, index, &status);
	index = 1;
	close(pipefd[1]);
	manage_fork(fd, pipefd, args, index, &status);
	manage_parent(&status);
	close(pipefd[0]);
	exit_free(args, 0);
}

