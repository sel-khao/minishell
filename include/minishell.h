/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:00 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/10 19:44:02 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WORD       1
# define EOF        2
# define REDIRECT   3
# define PIPE       4
# define HEREDOC    5
# define VAR		9
# define INFILE		10
# define OUTFILE	11
# define APPEND		12

# define LLONG_MIN 9223372036854775808ULL
# define LLONG_MAX 9223372036854775807ULL

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>// access, fork, execve, chdir, dup, pipe, read, close
# include <fcntl.h>// open, unlink
# include <string.h>// strerror
# include <sys/types.h>// wait, waitpid, wait3, wait4, stat-related types
# include <sys/wait.h>// wait, waitpid, wait3, wait4
# include <sys/stat.h>// stat, lstat, fstat
# include <signal.h>// signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>// opendir, readdir, closedir
# include <curses.h>// for termcap on some systems
# include <sys/ioctl.h>// ioctl
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

extern int	g_status;

# define RESET   "\033[0m"
# define BLUE    "\033[34m"
# define CYAN    "\033[36m"
# define BOLD    "\033[1m"

typedef struct s_redir
{
	char			*filename;
	int				type;//infile or outfile
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;//for kri
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*value;
	int				type;
	char			quote;
	struct s_token	*next;
}	t_token;

typedef struct s_expand
{
	char		**res;
	const char	*input;
	char		**envp;
	int			*es;
	int			*i;
}	t_expand;

typedef struct s_shell
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	int		es;
	int		i;
	int		pipe;
	pid_t	pids[4000];
}	t_shell;

typedef struct s_fd
{
	int	input;
	int	output;
}	t_fd;

char	*process_quotes(char *word);
int		in_quotes(char *input, int pos);
int		is_word(char c);
int		is_space(char c);
int		is_special(char c);
int		mult_redir(char *input);

int		validate_quote(char *str);
int		validate_pipe(char *input);
int		validate_input(char *input);
int		validate_redirection(char *input);
int		validate_redirection(char *input);
int		validate_heredoc(char **input);

int		handle_redirections(t_cmd *cmd);
int		handle_redirection(char **input);
void	handle_special(t_shell *shell, char *input, int *i);
void	handle_heredoc(char *delimiter, char **envp, t_cmd *cmd, int *es);

char	**add_word(char **argv, char *word);
int		heredoc_pipe(const char *delimiter, char **envp, int *es);
char	*extract_token(const char *input, int start, int end);

void	free_tokens(t_token *tokens);
void	free_argv(char **argv);
void	free_cmds(t_cmd *cmds);
void	free_all(t_shell *shell);
void	free_redir(t_redir *redir);
void	free_arr(char **str, char **new);

void	check_redi(t_cmd *cmd, t_token **tmp);
void	ft_readline(t_shell *shell);
void	init(t_cmd *cmd);
char	**initialize_shell(t_shell *shell, char **envp);

void	parsing(t_shell *shell, char **envp);
void	create_token(t_shell *shell, char *input, int *i);
void	tok_cmd(t_shell *shell, char **envp);

char	*extract_quoted(char *input, int *i);

void	add_token(t_shell *shell, char *value, int type, char quote_type);
void	tokenadd_back(t_token **lst, t_token *new);
void	tokenize(t_shell *shell);

void	check_type(t_token **tmp, t_cmd *cmd, char **envp, int *es);
void	check_type2(t_token **tmp, t_cmd **cmd);
void	add_redir(t_redir **redir_list, char *filename, int type);

void	check_delim(t_token **tmp, char **envp, t_cmd *cmd, int *es);

char	*expand_var(const char *input, char **envp, int *es);
char	*env_value(char **envp, char *key);
char	*append_char(char *base, char c);
char	*str_append(char *base, const char *to_add);

int		exit_shell(int status, t_shell *shell, char **envp, char **str, t_cmd *tmp);
int		print_exp(char **str);
int		check_same(char *str, char **envp);
int		match_word(char *str, char **envp);
int		unset(char **str, char **envp);

int		count_pipe(t_shell *shell);
int		pipex(t_shell *shell, char **envp);

int		exec_external(t_shell *shell, char **args, char **envp, t_fd *t);

int		is_builtin(char *cmd);
int		cd(char **path);
int		pwd(void);
int		ft_echo(char **str);
int		env(char **envp);
char	**export(char **env, char **str, int *es);

char	**add_exp(char **str, char **envp, int *es);
char	**dup_env(char **envp);
char	**execute(t_shell *shell, char **cmd, char *envp[], t_cmd *tmp);
char	*ft_rmchar(char *str, char c);

void	start_signals(void);
void	signal_handler(int sig);

void	restore_fds(int in, int out);

void	free_matrix(char **matrix);//per mettere in ordine env
int		matrix_len(char **matrix);
char	**order_env(char **envp);
char	**matrix_dup(char **old_mtx);

#endif