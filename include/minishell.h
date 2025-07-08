/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:00 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/08 18:48:20 by sara             ###   ########.fr       */
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

typedef struct s_shell
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
}	t_shell;


int		is_word(char c);
int		is_space(char c);
int		is_special(char c);
int		mult_redir(char *input);
int		in_quotes(char *input, int i);

int		validate_quote(char *str);
int		validate_pipe(char *input);
int		validate_input(char *input);
int		validate_redirection(char *input);
int		validate_redirection(char *input);
int		validate_heredoc(char **input);

char	**add_word(char **argv, char *word);
char	*extract_token(const char *input, int start, int end);
void	free_cmds(t_cmd *cmds);
void	free_tokens(t_token *tokens);
void	free_redir(t_redir *redir);
void	free_argv(char **argv);
void	free_all(t_shell *shell);
void	check_redi(t_cmd *cmd, t_token **tmp);

void	init(t_cmd *cmd);
void	ft_readline(t_shell *shell);

void	parsing(t_shell *shell, char **envp);
void	create_token(t_shell *shell, char *input, int *i);
void	tok_cmd(t_shell *shell, char **envp);

char *process_quotes(char *word);
char	*extract_quoted(char *input, int *i);

void	add_token(t_shell *shell, char *value, int type, char quote_type);
void	tokenadd_back(t_token **lst, t_token *new);

void	handle_special(t_shell *shell, char *input, int *i);

void	tokenize(t_shell *shell);
void	check_type(t_token **tmp, t_cmd *cmd, char **envp);
void	check_type2(t_token **tmp, t_cmd **cmd);
void check_delim(t_token **tmp, char **envp);
void	add_redir(t_redir **redir_list, char *filename, int type);
void handle_heredoc(char *delimiter, char **envp);
int		heredoc_pipe(const char *delimiter, char **envp);

char	*expand_var(const char *input, char **envp);
char	*env_value(char **envp, char *key);
char	*append_char(char *base, char c);
char	*str_append(char *base, const char *to_add);

int	exit_shell(int status, t_shell *shell, char **envp, char **str);
int		print_exp(char **str);
int		check_same(char *str, char **envp);
int		match_word(char *str, char **envp);
int		unset(char **str, char **envp);
int		ft_strcmp(char *s1, const char *s2);
int		pipex(t_shell *shell, char **envp);

int		handle_redirections(t_cmd *cmd);

int		exec_external(t_cmd *cmd, char **args, char **envp);

char	**add_exp(char **str, char **envp);
char	**dup_env(char **envp);
char	**execute(t_shell *shell, char **cmd, char *envp[]);
char	*ft_rmchar(char *str, char c);

void	free_arr(char **str, char **new);
void	start_signals(void);

void	restore_fds(int in, int out);

#endif