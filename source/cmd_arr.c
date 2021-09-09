#include "minishell.h"

int	get_cmd_char(char **cmd)
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
		if (ft_strnstr("echo", cmd[0], ft_strlen(cmd[0])) || ft_strnstr("cd", cmd[0], ft_strlen(cmd[0])))
			g_shell.arg = cmd[1];
		if (ft_strnstr(cmds[i], cmd[0], ft_strlen(cmd[0])))
		{
			return (i);
		}
	}
	return (-1);
}

void	cmd_func(int cmd)
{
	void	(*cmds[7])(void);
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
			cmds[i]();
	}
	
	// cmds[3] = export;
}

// our command
int	exec_ocmd(char **cmd)
{
	int	i;
	int	j;

	i = -1;
	// while (cmd[++i])
	// {
		j = get_cmd_char(cmd);
		if (j != -1)
		{
			cmd_func(j);
			printf("	Exec command\n");
			return (1);
		}
	// }
	return (0);
}