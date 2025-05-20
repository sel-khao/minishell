/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:00 by sel-khao          #+#    #+#             */
/*   Updated: 2025/05/20 09:21:11 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TOK_CMD        1   //
# define TOK_ARG        2   // "-l", "/home/user"
# define TOK_REDIRECT    3  // Redirect operator ">", "<", ">>"
# define TOK_PIPE        4   //  "|"
# define TOK_HEREDOC    5   // "<<"
# define DOLLAR
# define SPACES

# include <stdio.h>        // printf, perror
# include <stdlib.h>       // malloc, free, exit, getenv
# include <unistd.h>       // write, access, fork, execve, chdir, getcwd, dup, dup2, pipe, isatty, ttyname, ttyslot, read, close
# include <fcntl.h>        // open, unlink
# include <string.h>       // strerror
# include <sys/types.h>    // wait, waitpid, wait3, wait4, stat-related types
# include <sys/wait.h>     // wait, waitpid, wait3, wait4
# include <sys/stat.h>     // stat, lstat, fstat
# include <signal.h>       // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>       // opendir, readdir, closedir
# include <termios.h>      // tcsetattr, tcgetattr
# include <termcap.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>       // May be needed for termcap on some systems
# include <sys/ioctl.h>    // ioctl
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd
{
	int				append; 
	int				heredoc;
	char			**argv;//for kri
	char			*infile;
	char			*outfile;
	char			*delim;
	struct s_cmd	*next; 
}	t_cmd;

typedef struct s_token//for parsial strings
{
	char			*value; 
	int				type; 
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
}	t_shell;

void	free_all(t_shell *shell);
int		validate_quote(char *str);
int		validate_pipe(char *input);
int		validate_input(char *input);
int		validate_redirection(char *input);
int		validate_redirection(char *input);

void	tokenize(t_shell *shell);
void	ft_readline(t_shell *shell);

#endif