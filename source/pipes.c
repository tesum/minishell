#include "minishell.h"

int	pipes(int argc, char **env)
{
	t_pipex	pipex;
	t_list *cmd;
	// t_list *tmp;
	
	(void)argc;
	cmd = g_shell.cmd;
	// tmp = cmd;
	pipex.c_pipe = ft_lstsize(g_shell.cmd);
	g_shell.pid = malloc(sizeof(pid_t) * (pipex.c_pipe + 1));
	// dup2(pipex.pipes[pipex.iter][0], 0);
	// dup2(pipex.pipes[pipex.iter][1], 1);
	create_pipes(&pipex, argc);
	get_path(&pipex, env);
	pipex.iter = 0;
	exc_dup(&pipex);
	// printf("fgg\n");
	pipex.iter++;
	// close(0);
	// close(1);
	// dup2(pipex.pipes[pipex.iter][0], 0);
	// dup2(pipex.pipes[pipex.iter][1], 1);
		// exc_dup(&pipex);
	while (cmd)
	{
	printf("ara ara %d %d\n",ft_lstsize(g_shell.cmd), pipex.iter);
	// 	if (pipex.iter == ft_lstsize(g_shell.cmd))
	// 	{
	// 		dup2(pipex.pipes[pipex.iter][1], g_shell.fd_1);
	// printf("oro oro %d %d\n", ft_lstsize(g_shell.cmd), pipex.iter);
	// 	}

		// exc_dup(&pipex);
		exc_cmd(&pipex, env, cmd, argc);
		cmd = cmd->next;

	}
	// exc_cmd(&pipex, env, cmd, argc);
	// 	pipex.iter++;
	// exc_dup(&pipex);
	close(pipex.pipes[0][0]);
	close(pipex.pipes[0][1]);
	close(pipex.pipes[1][0]);
	close(pipex.pipes[1][1]);
	close(pipex.pipes[2][0]);
	close(pipex.pipes[2][1]);
	// close(pipex.pipes[argc - 2][1]);
	return (0);
}
