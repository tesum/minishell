#include "minishell.h"

int	get_cmd_char(char *cmd)
{
	int		i;
	static char	*cmds[8];

	i = -1;
	cmds[0] = "echo";
	cmds[1] = "cd";
	cmds[2] = "pwd";
	cmds[3] = "export";
	cmds[4] = "unset";
	cmds[5] = "env";
	cmds[6] = "exit";
	cmds[7] = "\0";
	while (cmds[++i])
	{
		// if (ft_strnstr("echo", cmd, ft_strlen(cmd)) || ft_strnstr("cd", cmd, ft_strlen(cmd)))
		// 	g_shell.arg = cmd[1];
		if (ft_strnstr(cmds[i], cmd, ft_strlen(cmd)) && ft_strlen(cmds[i]) == ft_strlen(cmd))
			return (i);
	}
	return (-1);
}

void	cmd_func(int cmd, char **cmd_ex)
{
	void	(*cmds[7])(char **cmd);
	int		i;

	cmds[0] = ft_echo;
	cmds[1] = ft_cd;
	cmds[2] = ft_pwd;
	cmds[3] = ft_export;
	cmds[4] = ft_unset;
	cmds[5] = ft_env;
	cmds[6] = ft_exit;
	i = -1;
	while (cmds[++i])
	{
		if (i == cmd)
			cmds[i](cmd_ex);
	}
}

void	cleaning(void)
{
	ft_lstclear(&((t_command *)g_shell.cmd->content)->argv, free);
	free(((t_command *)g_shell.cmd->content)->redirect);
	free(g_shell.cmd->content);
	g_shell.cmd->content = NULL;
	free(g_shell.cmd);
	g_shell.cmd = NULL;
	ft_lstadd_back(&g_shell.cmd, ft_lstnew((void *)command_new()));
}

// our command
int	builtins(char **cmd)
{
	int	i;
	int	j;

	i = -1;
	// while (cmd[++i])
	// {
		j = get_cmd_char(cmd[0]);
		if (j != -1)
		{
			cmd_func(j, cmd);
			// free(g_shell.cmd);
			// close(g_shell.fd);
			// close(1);
			// dup(1);
			// dup2(g_shell.fd_1, 1);
			// cleaning();
			return (1);
		}
	// }
	// cleaning();
	return (0);
}