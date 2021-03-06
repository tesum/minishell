/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:59:34 by caugusta          #+#    #+#             */
/*   Updated: 2021/10/18 17:09:44 by caugusta         ###   ########.fr       */
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
	t_list	*cmd;
	int		fd_1;
	int		fd_0;
	int		result;
	int		signal;
}				t_shell;

typedef struct s_pipex
{
	t_list	*cmd;
	int		c_pipe;
	int		iter;
	int		flag;
}			t_pipex;

t_shell	g_shell;

//signal
void		ctrl_c(int signal);

// builtins
void		ft_pwd(char **argv);
void		ft_echo(char **argv);
void		ft_cd(char **argv);
void		ft_unset(char **argv);
void		ft_export(char **argv);
void		ft_env(char **argv);
void		ft_exit(char **argv);

// env
t_env		*init_env(char **env);
t_env		*new_env(char *str, int env, int exp);
void		add_back_env(t_env **env, t_env *new);
void		logic_export(int *flags, int i, t_env *env, char *arg);
t_env		*find_list_env(t_env *env, char *str);
void		edit_shlvl(t_env *env);
void		start_pwd(t_env *env);
void		export_get_value(char *arg, int i, char **value, int f_plus);

// exec
void		executing(t_list *lst_cmd);
int			builtins(char **cmd);

// parser
int			preparser(char const *input);
void		parser(char const *input);
char		*other_handler(char const *input, int *i);
void		pipe_handler(int *i);
char		*double_redirect_handler(char const *input, int *i, \
			int *this_is_redirect);
char		*limiter_handler(char *rd, char *limiter);
char		*dollar(char *input, int *i);
void		who_is_your_daddy(void);
char		*clear_quotes(char *input);

// pipes
void		pipes(int argc);
pid_t		*init_pipes(int argc, t_pipex *pipex, int *a, int *b);
void		closer_pipes(int *a, int *b);

// utils
t_command	*command_new(void);
char		**set_command_struct(t_list *lst_cmd);
void		edit_env_line(t_env *env, char *find, char *edit);
char		**env_arr(t_env *env, int export);
void		err_msg(char *str);
void		sup_dup(int *fd);
void		try_free(void *target);
void		try_free3(void *a, void *b, void *c);
void		cleaning(void);
char		**free_2d_arr(char **arr);
void		exit_error(char *str, int code);
void		status_handler(void);
int			try_dup(int fd);
int			try_dup2(int fd, int fd2);

#endif