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
		if (ft_strnstr(cmds[i], cmd, ft_strlen(cmd)))
			return (i);
	}
	return (-1);
}

void	cmd_func(int cmd, char **cmd_ex)
{
	void	(*cmds[7])(char **cmd);
	int		i;

	cmds[0] = echo;
	cmds[1] = cd;
	cmds[2] = pwd;
	cmds[3] = export;
	cmds[4] = unset;
	cmds[5] = o_env;
	cmds[6] = o_exit;
	i = -1;
	while (cmds[++i])
	{
		if (i == cmd)
			cmds[i](cmd_ex);
	}
}

// our command
int	exec_ocmd(char **cmd)
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
			printf("	Exec command\n");
			return (1);
		}
	// }
	return (0);
}