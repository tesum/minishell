#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_shell
{
	char	**env;
	int		result;
}				t_shell;

t_shell	g_shell;

// PREPERSER
void	init_shell(int argc, char **argv, char **env);
int		preparser(char *input);
int		check_second_quote(char quote, char *input, int *i);
int		check_begin(char *input);

// PERSER
void	parser(char *input);
char	*single_quote(char *input, int *i);
char	*delete_simbol(char *input, int *i);
char	*double_quote(char *input, int *i);
char	*dollar(char *input, int *i);
char	*dollar_utils(char **input, int *i, int *k);
char	*replace_variable(char *str, char *str_replace, int *start, int end);
char	*replace_str(char *input, char *str_replace, int *start, int end);
void	error_malloc(char *a, char *b, char *c);
char	*pipe_handler(char *input, int *i);
char	*double_redirect_handler(char *input, int *i);
char	*redirect_handler(char *input, int *i);

// exec
char	*correct_path(char **cmd);
char	**find_path(void);
void	executing(char **cmd);
void	free_2d_arr(char **arr);
void	exit_error(char *str, int code);

//signal
void	signal_handler(void);
void	ctrl_c(int signal);

// biltins
void	builtins(char **cmd);
void	ft_echo(char **cmd);
void	ft_cd(char **cmd);
void	ft_pwd(char **cmd);
void	ft_export(char **cmd);
void	ft_unset(char **cmd);
void	ft_env(char **cmd);
void	ft_exit(char **cmd);

#endif