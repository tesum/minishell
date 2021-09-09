#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

// PREPERSER

int		preparser(char *input);
int		check_second_quote(char quote, char *input, int *i);
int		check_begin(char *input);

// PERSER
void	parser(char *input, char **env);
char	*single_quote(char *input, int *i);
char	*delete_simbol(char *input, int *i);
char	*double_quote(char *input, char **env, int *i);
char	*dollar(char *input, char **env, int *i);
char	*dollar_utils(char *input, int *i, int *k);
char	*replace_variable(char *str, char *str_replace, int *start, int end);
char	*replace_str(char *input, char *str_replace, int *start, int end);
void	error_malloc(char *a, char *b, char *c);
char	*pipe_handler(char *input, int *i);
char	*double_redirect_handler(char *input, int *i);
char	*redirect_handler(char *input, int *i);

// exec
char	*correct_path(char **env, char **cmd);
char	**find_path(char **env);
void	executing(char **env, char **cmd);
void	free_2d_arr(char **arr);
void	exit_error(char *str, int code);

// COMMAND
int		exec_ocmd(char **env, char **cmd);
void	pwd(char **env);
void	echo(char **env);
void	cd(char **env);

#endif