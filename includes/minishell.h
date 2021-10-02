#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_command
{
	t_list	*argv;
	t_list	*redirect;
	int		complete;
}				t_command;

typedef struct s_shell
{
	char	**env;
	char	*pwd;
	pid_t	*pid;
	int		fd;
	int		fd_1;
	int		fd_0;
	int		result;
	int		error_malloc;
	t_list	*cmd;
}				t_shell;

typedef struct s_pipex
{
	t_list	*cmd;
	int		c_pipe;
	int		iter;
	int		flag;
	char	**path;
}			t_pipex;

t_shell	g_shell;

// PREPERSER
void	init_shell(int argc, char **argv, char **env);
int		preparser(char const *input);
int		check_second_quote(char quote, char const *input, int *i);
int		check_begin(char const *input);
int		check_invalid(char const *input);

// PERSER
void	post_modern_parser(char *input, char **formated);
void	parser(char const *input);
int		set_arg(char *str, int *this_is_redirect);
char	*quote_handler(char *input, int quote, int *i);
char	*other_handler(char const *input, int *i);
void	error_malloc(char *a, char *b, char *c);
char	*dollar(char *input, int *i);
char	*find_env(char *str);
char	*replace_variable(char *str, char *str_replace, int *start, int end);
char	*replace_str(char *input, char *str_replace, int *start, int end);
int		pipe_handler(int *i);
char	*double_redirect_handler(char const *input, int *i, \
			int *this_is_redirect);
char	*redirect_handler(char const *input, int *i, int *this_is_redirect);
int		set_redirect(char **str, int *this_is_redirect);
char	*clear_quotes(char *str);

// exec
char	*correct_path(char **cmd);
char	**find_path(void);
void	executing(t_list *cmd);
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
void	pwd(char **arg);
void	echo(char **arg);
// func //
int		flag_n(char	**argv, int i);
int		kill_n(char **argv, int i);
//      //
void	cd(char **arg);
void	unset(char **arg);
void	export(char **arg);
void	o_env(char **arg);
void	o_exit(char **arg);

// arr_utils
char	**arr_add_back(char **array, char *content);
char	**arr_add_front(char **array, char *content);
char	**arr_del_str(char **array, char *str);
char	**arr_copy_n_elem(char **array, int n);
int		arr_size(char **array);

// command utils
t_command	*command_new(void);
void		print_t_list(void);

void	who_is_your_daddy(void);
char	**set_command_struct(t_list *pipe);
char	*get_pwd(void);

void	pipes(int argc);
void	create_pipes(t_pipex *pipex, int count);
void	get_path(t_pipex *pipex, char **env);
void	exc_dup(t_pipex *pipex);
void	exc_cmd(t_pipex *pipex, char **env, t_list *cmd, int argc);

void	cleaning(void);
int		parsing(void);

#endif