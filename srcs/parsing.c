/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:25:44 by dernst            #+#    #+#             */
/*   Updated: 2025/04/01 15:14:58 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <linux/limits.h>

char	*get_env_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	**parse_env(char *path)
{
	char	*start_path;
	char	**splited_path;

	start_path = path + 5;
	splited_path = ft_split(start_path, ':');
	return (splited_path);
}

char	*check_valid_command(char **splited_path, char *command)
{
	char	path_test[PATH_MAX];
	char	*final_path;

	while (*splited_path != NULL)
	{
		ft_strlcpy(path_test, *splited_path, ft_strlen(*splited_path) + 1);
		ft_strlcat(path_test, "/", ft_strlen(path_test) + 2);
		ft_strlcat(path_test, command, ft_strlen(path_test)
			+ ft_strlen(command) + 1);
		if (access(path_test, F_OK | X_OK) == 0)
		{
			final_path = ft_strdup(path_test);
			if (!final_path)
				return (NULL);
			return (final_path);
		}
		splited_path++;
		ft_strlcpy(path_test, "\0", 1);
	}
	return (NULL);
}

t_args	parsing(char **argv, char *path, t_fd fd, int *pipefd)
{
	t_args	args;
	char	**splited_path;

	args = init_arg();
	if (pipe(pipefd) < 0)
		exit_free(args, EPIPE, fd, pipefd);
	args.arg1 = ft_split(argv[2], ' ');
	if (!args.arg1)
		exit_free(args, ENOMEM, fd, pipefd);
	args.command1 = args.arg1[0];
	args.arg2 = ft_split(argv[3], ' ');
	if (!args.arg2)
		exit_free(args, ENOMEM, fd, pipefd);
	args.command2 = args.arg2[0];
	splited_path = parse_env(path);
	if (!splited_path)
		exit_free(args, 1, fd, pipefd);
	args.command1 = check_valid_command(splited_path, args.command1);
	args.command2 = check_valid_command(splited_path, args.command2);
	cleanup_split(splited_path);
	if (!args.command2)
		exit_free(args, 127, fd, pipefd);
	return (args);
}
