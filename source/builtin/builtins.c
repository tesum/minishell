#include "minishell.h"

void	builtins(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5) || !ft_strncmp(cmd[0], "ECHO", 5))
		ft_echo(cmd);
	if (!ft_strncmp(cmd[0], "cd", 3))
		ft_cd(cmd);
	// if (!ft_strncmp(cmd[0], "pwd", 3) || !ft_strncmp(cmd[0], "PWD", 3))
	// 	ft_pwd(cmd);
	if (!ft_strncmp(cmd[0], "export", 7))
		ft_export(cmd);
	if (!ft_strncmp(cmd[0], "unset", 6))
		ft_unset(cmd);
	if (!ft_strncmp(cmd[0], "env", 4) || !ft_strncmp(cmd[0], "ENV", 4))
		ft_env(cmd);
	if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd);
}

void	ft_echo(char **cmd)
{
	(void)cmd;
	printf("NOT DONE\n");
	exit(12);
}

void	ft_cd(char **cmd)
{
	(void)cmd;
	printf("NOT DONE\n");
	exit(12);
}

void	ft_pwd(char **cmd)
{
	(void)cmd;
	printf("NOT DONE\n");
	exit(12);
}

void	ft_export(char **cmd)
{
	(void)cmd;
	printf("NOT DONE\n");
	exit(12);
}

void	ft_unset(char **cmd)
{
	(void)cmd;
	printf("NOT DONE\n");
	exit(12);
}

void	ft_env(char **cmd)
{
	(void)cmd;
	printf("NOT DONE\n");
	exit(12);
}

void	ft_exit(char **cmd)
{
	(void)cmd;
	printf("NOT DONE\n");
	exit(12);
}
