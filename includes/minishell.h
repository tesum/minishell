#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_command
{
	char				**argv;
	char				**redirect;
	struct s_command	*next;
}				t_command;

typedef struct s_shell
{
	char	**env;
	char	*arg;
	int		result;
	t_command	*command;
}				t_shell;

t_shell	g_shell;

// PREPERSER
void	init_shell(int argc, char **argv, char **env);
int		preparser(char *input);
int		check_second_quote(char quote, char *input, int *i);
int		check_begin(char *input);

// PERSER
void	parser(char *input);
void	post_modern_parser(char *input, char **formated);
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
char	**free_2d_arr(char **arr);
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

// COMMAND
int		exec_ocmd(char **cmd);
void	pwd(void);
void	echo(void);
void	cd(void);
void	unset(void);
void	export(void);
void	o_env(void);
void	o_exit(void);

// arr_utils
char	**arr_add_back(char **array, char *content);
char	**arr_add_front(char **array, char *content);
char	**arr_del_str(char **array, char *str);
char	**arr_copy_n_elem(char **array, int n);
int		arr_size(char **array);

// command utils
void	command_add_back(t_command **lst, t_command *new);
void	command_add_front(t_command **lst, t_command *new);
t_command	*command_last(t_command *lst);
t_command	*command_new(char	**formated);
int	command_size(t_command *lst);

void	who_is_your_daddy(char *input, char **formated);
void	set_command_struct(char **formated);

#endif