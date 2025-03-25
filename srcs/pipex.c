/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:11:03 by dernst            #+#    #+#             */
/*   Updated: 2025/03/25 16:13:49 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//! Check the relink with the .h
//! echo $? To check the good return 126 (Pipe fails for exemple) search online

#include "libft.h"
#include "unistd.h"
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"

//void test()
//{
//	int fd;
//	int fd2;
//	char *argv[] = {"cat", NULL};

//	fd = open("Makefile", O_RDONLY);
//	fd2 = open("output", O_CREAT | O_WRONLY);
//	dup2(fd, STDIN_FILENO);
//	dup2(fd2, STDOUT_FILENO);
//	execve("/bin/cat", argv, __environ);
	
//}

void	manage_child(t_fd fd, int *pipefd, t_args args, int index)
{
	char	*cmd_path;
	if (index == 0)
	{
		dup2(fd.fd_in, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		cmd_path = ft_strjoin("/bin/", args.command1);
		execve(cmd_path, args.arg1, NULL);	
		free(cmd_path);
		exit(1);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fd.fd_out, STDOUT_FILENO);
		close(pipefd[1]);
		cmd_path = ft_strjoin("/bin/", args.command2);
		execve(cmd_path, args.arg2, NULL);
		free(cmd_path);
	}
	exit(1);
}

int	manage_fork(t_fd fd, int *pipefd, t_args args, int index)
{
	int	pid;
	pid = fork();
	
	if (pid == -1)
		return(1);
	else if (pid == 0)
		manage_child(fd, pipefd, args, index);
	return (0);
}
int	main(int ac, char **av)
{
	t_args	args;
	t_fd	fd;
	int		index;
	int		pipefd[2];
	
	if (ac != 5)
		return (1);

	fd = init_fd(av);
	args = parsing(av);
	index = 0;
	pipe(pipefd);
	manage_fork(fd, pipefd, args, index);
	index = 1;
	manage_fork(fd, pipefd, args, index);
}

//int main(int argc, char	**argv)
//{

//	t_args	args;
//	int	pipefd[2];
//	int pid;
//	int fd;
//	int fd2;
//	int i;
//	int status;

//	status = 0;

//	if (argc != 5)
//		return(1);
//	args = parsing(argv);
	
//	i = 0;
//	fd = open(argv[1], O_RDONLY);
//	fd2 = open(argv[4], O_CREAT | O_WRONLY);
//	pipe(pipefd);
//	while (i < 2)
//	{
//		pid = fork();
//		if (pid == 0)
//		{
//			if (i == 0)
//			{
//				dup2(fd, STDIN_FILENO);
//				dup2(pipefd[1], STDOUT_FILENO);
//				execve(ft_strjoin("/bin/", argv[2]), args.arg1, NULL);
//			}
//			if (i == 1)
//			{
//				dup2(pipefd[0], STDIN_FILENO);
//				dup2(fd2, STDOUT_FILENO);
//				execve(ft_strjoin("/bin/", argv[3]), args.arg2, NULL);
//			}
//		}
//		else
//			wait(NULL);
//		i++;
//	}
//	exit(0);
//	return (0);

//}

