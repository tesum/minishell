/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:59:34 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/13 09:42:40 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}				t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				env;
	int				exp;
	struct s_env	*next;
}				t_env;

typedef struct s_shell
{
	char	**env;
	t_env	*new_env;
	pid_t	*pid;
	t_list	*cmd;
	int		fd_1;
	int		fd_0;
	int		result;
	int		signal;
}				t_shell;

typedef struct s_pipex
{
	char	**path;
	t_list	*cmd;
	int		c_pipe;
	int		iter;
	int		flag;
}			t_pipex;

t_shell	g_shell;

// PREPERSER
void		init_shell(int argc, char **argv, char **env);
int			preparser(char const *input);
int			check_second_quote(char quote, char const *input, int *i);
int			check_begin(char const *input);
int			check_invalid(char const *input);

// PARSER
void		parser(char const *input);
int			set_arg(char *str, int *this_is_redirect);
char		*other_handler(char const *input, int *i);
char		*dollar(char *input, int *i);
char		*find_env(char *str);
char		*replace_variable(char *str, char *str_replace, \
				int *start, int end);
char		*replace_str(char *input, char *str_replace, int *start, int end);
void		pipe_handler(int *i);
char		*double_redirect_handler(char const *input, int *i, \
				int *this_is_redirect);
char		*redirect_handler(char const *input, int *i, int *this_is_redirect);
int			set_redirect(char *str);
char		*clear_quotes(char *str);
char		*limiter_handler(char *rd, char *limiter);

// exec
char		*correct_path(char **cmd);
char		**find_path(void);
void		executing(t_list *cmd);
char		**free_2d_arr(char **arr);
void		exit_error(char *str, int code);

//signal
void		ctrl_c(int signal);
void		ctrl_c_(int signal);

// builtins
int			builtins(char **cmd);
void		ft_pwd(char **argv);
void		ft_echo(char **argv);
void		ft_cd(char **argv);
void		ft_unset(char **argv);
void		ft_export(char **argv);
void		ft_env(char **argv);
void		ft_exit(char **argv);

// command utils
t_command	*command_new(void);
void		print_t_list(void);

void		who_is_your_daddy(void);
char		**set_command_struct(t_list *pipe);

void		pipes(int argc);
void		create_pipes(t_pipex *pipex, int count);
void		get_path(t_pipex *pipex, char **env);
void		exc_dup(t_pipex *pipex);
void		exc_cmd(t_pipex *pipex, char **env, t_list *cmd, int argc);

void		cleaning(void);
int			parsing(void);

t_env		*init_env(char **env);
t_env		*new_env(char *key, int env, int exp);
t_env		*find_list_env(t_env *env, char *str);
void		edit_env_line(t_env *env, char *find, char *edit);
void		edit_shlvl(t_env *env);
void		add_back_env(t_env **env, t_env *new);
void		exit_malloc_error(void);
char		**env_arr(t_env *new_env, int export);
int			env_size(t_env *env);
void		export_plus(t_env *env, char *key, char *value);
void		logic_export(int *flags, int i, t_env *env, char *arg);
void		clear_env(t_env **env);

void		try_free(void *target);

#endif