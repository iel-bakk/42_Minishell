/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:14:04 by amounach          #+#    #+#             */
/*   Updated: 2023/01/11 17:44:45 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

typedef enum e_tokens
{
	NONE,
	PIPE,
	WSPACE,
	SINGLE_Q,
	DOUBLE_Q,
	RE_INPUT,
	RE_OUTPUT,
	APPEND,
	HEREDOC,
	WORD,
	VARIABLE,
}	t_etokens;

typedef struct s_params
{
	char			*line;
	char			*buffer;
	int				i;
	int				j;
	int				cpt;
	int				count;
	int				len;
}					t_params;

typedef struct s_tokens
{
	int				type;
	char			*value;
	int				valid;
	int				space;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}					t_tokens;

typedef struct s_redir
{
	char			*file_name;
	int				type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_final
{
	char			**str;
	t_redir			*list;
	struct s_final	*next;
}					t_final;

typedef struct s_env
{
	char			*v_name;
	char			*v_value;
	struct s_env	*next;
}					t_env;

typedef struct node_g
{
	void			*pointer;
	struct node_g	*next;
}					t_node_g;

typedef struct garbage_collect
{
	t_node_g		*head;
}					t_garbage;

typedef struct s_globals
{
	t_garbage		*garbage;
	int				global;
	int				status_sign;
}					t_globals;

typedef struct s_built
{
	t_final	*cmd;
	t_env	**list;
}					t_built;

typedef struct s_eof
{
	char	*line;
	char	*buff;
	int		idx;
	char	*tmp;
	char	*tmp2;
}	t_eof;

typedef struct s_main
{
	char		*line;
	t_env		*env_head;
	t_tokens	*tokens;
	int			sig;
}	t_main;

extern t_globals	g_tools;
// Tokenizer
t_tokens			*create_tokens(int type, char *value);
int					is_space(t_tokens **token, char *line);
int					is_pipe(t_tokens **tokens, char *line);
int					redi_type(int type);
int					is_redir(int type);
int					is_alpha_num(char c);

// main stuff
void				free_tokens(t_tokens *tok);
void				free_redir(t_redir *tok);
void				free_final(t_final *tok);

// Builtins
int					ft_pwd(void);

// Exit status
char				*check_status(char *str);
void				expand_status(t_params *param, char *status);
// Linked list utils
t_tokens			*new_node(int type, char *value);
void				delete_first_node(t_tokens **head);
void				push_front(t_tokens **head, t_tokens *node);
void				push_back(t_tokens **head, t_tokens *node);
void				display(t_tokens *head);

// Functions from libft and other projects
char				*ft_strdup(char *s1);
int					ft_strlen(char *str);
char				*ft_itoa(int n);
int					ft_strlcpy(char *dst, char *src, int dstsize);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_split(char *s, char c);
char				*malloc_word(char *str, char c);
char				**ft_free(char **str);
int					count_words(char *str, char c);
char				*get_variable_new_value(char *str, t_env *env);
int					ft_atoi(char *str);

// Syntax Error
int					pipe_error(t_tokens *token);
int					redirection_error(t_tokens *token);
int					input_append_error(t_tokens *token);
int					empty_quote(t_tokens *token);
int					redirection_error(t_tokens *token);
int					quotes_error(t_tokens *token);
int					heredoc_error(t_tokens *token);
int					error_checker(t_tokens *token);

// parsing functions
char				*get_v_name(char *str);
t_env				*no_env_found(void);
t_env				*creat_env_node(char *v_name);
t_env				*creat_env_list(char **env);
void				delete_onev(t_env **head, t_env *to_d);
void				delete_env_list(t_env **head);
void				delete_env_node(t_env **to_delete);
void				expande_variables(t_tokens *list, t_env *head);
void				change_value(t_tokens *token, t_env *env);
char				*get_variable(char *line, t_env *env);
int					increment(t_params *params);
void				get_last_word(t_params *params);
int					get_buffer(t_params *params, t_env *env);

void				intialize(t_params *params);
char				*get_env_value(char *env_name, t_env *env);
int					is_variable(char *line);
int					is_character(int c);
int					is_dollar(int c);
int					only_char(char c);
t_env				*mitirix_to_env(char *name, char *op_value,
						t_env *last, char *buff);

// jesus tests
t_tokens			*parse_line(char *line);
t_tokens			*get_special(char *line, int *i);
t_tokens			*get_word(char *line, int *i);
char				*allocat_word(char *line, int *i);
int					is_special(char c);
t_tokens			*get_left_out(char *line, int *i);
t_tokens			*get_right_out(char *line, int *i);
t_tokens			*get_pipe(int *i);
t_tokens			*get_double_quote(char *line, int *i);
char				*inside_double_quote(char *line, int *i);
char				*inside_single_quote(char *line, int *i);
t_tokens			*get_single_quote(char *line, int *i);
char				*join_and_free(char *s1, char *s2);
char				*get_env_value_(char *env_name, t_env *env);

// builtins
void				mi_env(t_env *list);
int					call_builtin(t_built built, int pip, int fd[2],
						int last);
int					mi_pwd(char **str);
void				push_back_env(t_env **head, t_env *node);
void				echo_print(int fd, char *str);
int					mi_echo(char **arg);
int					ft_strcmp(char *s1, char *s2);
int					check_n_option(char *str);
void				ft_putstr_fd(int fd, char *str);
void				mi_export(char **arg, t_env **list);
void				print_export(t_env *list);
int					valid_v_name(char *str);
void				export_cases(char **arg, t_env **list);
void				modify_envar(char *name, char *op_value, t_env **list);
void				try_to_creat(char *new, t_env **list);
void				ft_exit(char **str);
int					check_if_num(char *str);

// check if builtin or not
int					compare_to_biultin(char *str);
int					check_builtin(char **str, t_env *env);
void				non_builtin(char **param, char **env);

// creating a pipe
int					*creat_pipe(void);

// final linked list
t_final				*creat_final_node(int tab_len);
void				add_final_end(t_final **head, t_final *new);

// redirection functions
t_redir				*creat_redir_node(char *file_name, int type);
int					verify_is_word_type(t_tokens *test);
int					verify_is_redir_type(t_tokens *test);
int					calc_cmd_len(t_tokens *list);
t_final				*lvlup_ultimate(t_tokens **list, t_final **head);
void				final_command(t_final **head, t_tokens **list, int len);
t_final				*convert_from_tokens_to_final(t_tokens *list);
void				refill_param(t_final *command, t_tokens **buff, int len);
void				continue_param_fill(t_final *command, t_tokens **buff,
						int len);
void				copy_table(char **old, char **new, int old_len);

// non builtins tests
int					exec_cmd(t_final *cmd, char **env, int fd[2], int last);

void				lvlup_redir(t_tokens **list, t_final **head);
t_redir				*get_redir_list(t_tokens **list);
void				add_redir_end(t_redir **head, t_redir *new);

// execution test after parsing is done
char				*get_cmd_path(char *str, t_env *env);
char				*test_paths(char **paths, char *cmd);
int					launch_redir(t_redir *list);
void				exec_command(t_final *t, t_env **env);
char				**convert_from_env_to_tb(t_env *env);
int					execute(int fd[2], t_env **env, t_final *t, int last);
void				go_builtins(t_final *cmd, t_env **list);

// amounach
void				handler_c(int sig);
void				match_variables(t_env **env, char **str);
void				unset(t_env **env, char **str);
void				open_heredoc(t_tokens *token);
void				ft_cd(char **arg, t_env *list);
void				change_dir(char *old_pwd, t_env *list);
int					count_arg(char **str);
char				*change_file_name(char *file_name, int *idx);

void				free_redir_node(t_redir *f);
void				add_redir_to_list(t_tokens **token, t_final *cmd);
t_redir				*current_redir(t_tokens **token);

// garbage collector
void				*add_garbage(t_garbage *g, void *pointer);
void				free_garbage(t_garbage *g);

#endif