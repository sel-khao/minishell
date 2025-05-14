
#include "minishell.h"

void ft_readline(t_shell *shell)
{
    shell->input = readline("mininshell>");
    if (!shell->input)
        exit(0);
    if (shell->input[0])
        add_history(shell->input);
}