#include "minishell.h"

int	get_cmd_char(char *cmd)
{
	int		i;
	char	**cmds;

	i = -1;
	cmds = malloc(sizeof(char *) * 8);
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
		if (ft_strnstr(cmds[i], cmd, ft_strlen(cmd)))
			return (i);
	}
	free(cmds);
	return (-1);
}

void	cmd_func(int cmd, char **env)
{
	void	(*cmds[7])(char **env);
	int		i;

	cmds[0] = echo;
	cmds[1] = cd;
	cmds[2] = pwd;
	i = -1;
	while (cmds[++i])
	{
		if (i == cmd)
			cmds[i](env);
	}
	
	// cmds[3] = export;
}

// our command
int	exec_ocmd(char **env, char **cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		j = get_cmd_char(cmd[i]);
		if (j != -1)
		{
			cmd_func(j, env);
			printf("	Exec command\n");
			return (1);
		}
	}
	return (0);
}