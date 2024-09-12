/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:13:19 by achamsin          #+#    #+#             */
/*   Updated: 2024/09/12 18:06:49 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION -36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

typedef enum e_tokens
{
	TOKEN_PIPE,
	TOKEN_TRUNC,
	TOKEN_WORD,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF
}	t_tokens;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				hidden;
	struct s_env	*next;
}	t_env;

// export key=value

// env
// ...
// ...
// key=value
// export key
// env
// ...
// ...
// export
// export ...
// export ...
// export key
// !strchr(str, '=')
// add_tail(key, NULL, hidden = 1)
// print_full_env => export
// print_env => env => no display for hidden nodes

typedef struct s_mini
{
	t_token			*start;
	t_env			*env;
	t_env			*secret_env;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				error_num;
	int				no_exec;
}				t_mini;

typedef struct s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

// void	display_prompt();
void	shell_loop(t_mini *mini);
int		ignore_sep(char *line, int i);
void	ft_skip_space(const char *str, int *i);
int		check_quotes(const char *input);
void	ft_skip_space(const char *str, int *i);
void	type_arg(t_token *token, int separator);
void	display_tokens(t_token *token);

//ENV
int		is_env_char(int c);
int		ft_secret_env(t_env *env);
// void	squish_args(t_mini *mini);
t_token	*get_tokens(char *line);
int		env_init(t_mini *mini, char **env_array);
int		secret_env_init(t_mini *mini, char **env_array);
void	increment_shell_level(t_env *env);
char	*get_env_value(char *arg, t_env *env);
char	*get_env_name(char *dest, const char *src);
char	*get_var_value(const char *arg, int pos, t_env *env, int ret);
int		arg_alloc_len(const char *arg, t_env *env, int ret);
void	print_sorted_env(t_env *env);
int		is_valid_env(const char *env);
char	*env_to_str(t_env *lst);
void	split_key_value(const char *env_str, char **key, char **value);
char	*expander_str(t_mini *mini, char *str);
char	**expander(t_mini *mini, char **str);
size_t	equal_sign(char *str);
int		after_dol_lenght(char *str, int j);
int		question_mark(t_mini *mini, char **tmp);
size_t	quotes_lenght(char *str);
char	*delete_quotes(char *str, char c);
size_t	dollar_sign(char *str);
char	*char_to_str(char c);

//builtin_functions

int		ft_env(t_env *env);
int		ft_export(char **args, t_env **env, t_env **secret);
int		ft_unset(char **args, t_env **env);
void	ft_pwd(void);
int		cd_home(t_mini *mini);
int		update_oldpwd(t_mini *mini);
int		update_pwd(t_mini *mini);
int		cd_file(t_mini *mini, char *path);
char	*ft_pwd1(void);
int		cd_last(t_mini *mini);
int		cd_dash(t_mini *mini);
char	**cmd_tab(t_token *start);
int		ft_echo(char **args);
int		is_mixed(char *str);
int		exec_bin(char **args, t_env *env, t_mini *mini);

//FREE
void	free_tab(char **tab);
void	free_env(t_env *env);
void	free_token(t_token *start);

//FD
void	ft_close(int fd);
void	reset_std(t_mini *mini);
void	close_fds(t_mini *mini);
void	reset_fds(t_mini *mini);

//TYPE
int		is_type(t_token *token, int type);
int		is_types(t_token *token, char *types);
int		has_type(t_token *token, int type);
int		has_pipe(t_token *token);
t_token	*next_type(t_token *token, int type, int skip);

extern t_sig g_sig;
#endif