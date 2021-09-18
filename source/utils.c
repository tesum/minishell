#include "minishell.h"

void	create_pipes(t_pipex *pipex, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pipe(pipex->pipes[i]);
		i++;
	}
}

void	get_path(t_pipex *pipex, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], "PATH=", 5)) == 0)
		{
			pipex->path = ft_split(env[i] + 5, ':');
			return ;
		}
		i++;
	}
}

static void	close_excess_fd(t_pipex *all, int fd_in, int fd_out)
{
	int	j;

	j = 0;
	while (j < all->c_pipe)
	{
		if (j != fd_in && all->pipes[j][0])
			close(all->pipes[j][0]);
		if (j != fd_out && all->pipes[j][1])
			close(all->pipes[j][1]);
		j++;
	}
}

void	exc_dup(t_pipex *pipex)
{
	if (pipex->iter == 0)
	{
		// close(pipex->pipes[pipex->iter][0]);
		dup2(pipex->pipes[pipex->iter][1], 1);
		// close_excess_fd(pipex, 10000, 0);
	}
	else if (pipex->iter < pipex->c_pipe)
	{
		// if (pipex->iter != 1)
			// close(pipex->pipes[pipex->iter - 1][1]);
		dup2(pipex->pipes[pipex->iter - 1][0], 0);
		// close(pipex->pipes[pipex->iter][0]);
		dup2(pipex->pipes[pipex->iter][1], 1);
		close_excess_fd(pipex, pipex->iter - 1, pipex->iter);

	}
	else
	{
		// close(pipex->pipes[pipex->iter - 1][1]);
		dup2(pipex->pipes[pipex->iter - 1][0], 0);
		// close(pipex->pipes[pipex->iter - 1][0]);
		close_excess_fd(pipex, pipex->iter - 1, 10000);
		// dup2(pipex->pipes[pipex->iter][1], 1);
	}
	if (g_shell.fd)
		dup2(g_shell.fd, 1);
		

}

void	check_cmd(t_pipex *pipex, char *cmd)
{
	int		i;
	int		file;
	char	*path_cmd;

	i = 0;
	while (pipex->path[i])
	{
		path_cmd = ft_strjoin(pipex->path[i], "/");
		pipex->cmd = ft_strjoin(path_cmd, cmd);
		file = open(pipex->cmd, O_RDONLY);
		if (file != -1)
			return ;
		i++;
	}
	if (file == -1)
	{
		perror("Invalid command\n");
		exit (1);
	}
}

void	exc_cmd(t_pipex *pipex, char **env, t_list *cmd, int argc)
{
	// pid_t	pid;
	// int		exe;
	char	**lal;
	// char	**split_cmd;
	(void)env;
	(void)pipex;
	(void)argc;
	// who_is_your_daddy();
	// split_cmd = ft_split(cmd, ' ');
	// check_cmd(pipex, split_cmd[0]);
	g_shell.pid[pipex->iter] = fork();
	if (g_shell.pid[pipex->iter] != 0)
	{
		// waitpid(g_shell.pid[pipex->iter], &g_shell.result, 0);
		// g_shell.result /= 256;
		waitpid(-1, 0, 0);	
			close(pipex->pipes[pipex->iter][1]);
		// if (pipex->iter != ft_lstsize(g_shell.cmd))
	}
	else
	{
		// exc_dup(pipex);
	// printf("oro oro %d %d\n", ft_lstsize(g_shell.cmd), pipex->iter);
	// 	if (pipex->iter == ft_lstsize(g_shell.cmd))
	// 	{
	// 		// dup2(pipex->pipes[pipex->iter][1], g_shell.fd_1);
	// printf("oro oro %d %d\n", ft_lstsize(g_shell.cmd), pipex->iter);
	// 	}
		if (pipex->iter == 0)
		{
			// close(pipex->pipes[pipex->iter][0]);
			printf("ara ara %d %d\n",ft_lstsize(g_shell.cmd), pipex->iter);

			dup2(pipex->pipes[pipex->iter][1], 1);
			close_excess_fd(pipex, 10000, 0);
		}
		else if (pipex->iter < pipex->c_pipe)
		{
			// if (pipex->iter != 1)
				// close(pipex->pipes[pipex->iter - 1][1]);
			printf("LLLLLLLL\n");
			dup2(pipex->pipes[pipex->iter - 1][0], 0);
			printf("LLLLLLLL\n");
			// close(pipex->pipes[pipex->iter][0]);
			dup2(pipex->pipes[pipex->iter][1], 1);
			printf("LLLLLLLL\n");
			close_excess_fd(pipex, pipex->iter - 1, pipex->iter);
			printf("LLLLLLLL\n");

		}
		else
		{
			// close(pipex->pipes[pipex->iter - 1][1]);
			printf("AAAAA\n");
			dup2(pipex->pipes[pipex->iter - 1][0], 0);
			printf("AAAAA\n");
			// close(pipex->pipes[pipex->iter - 1][0]);
			close_excess_fd(pipex, pipex->iter - 1, 10000);
			dup2(pipex->pipes[pipex->iter][1], 1);
			printf("AAAAA\n");
		}
		if (g_shell.fd)
			dup2(g_shell.fd, 1);
		lal = set_command_struct(cmd);
		if (exec_ocmd(lal))
			exit(0);
		// else
			executing(lal);
		
		// exe = execve(pipex->cmd, split_cmd, env);
		// if (exe == -1)
		// 	perror("Error execute command\n");
		// exit (1);
	}
	pipex->iter++;

}
