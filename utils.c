
#include "minishell.h"

void ft_readline(t_shell *shell)
{
    shell->input = readline("mininshell>");
    if (!shell->input)
        exit(0);
    if (shell->input[0])
        add_history(shell->input);
}

{
    int s = 0;
    int d = 0; // single and double quote flags

    while (*input == ' ')
        input++;
    if (*input == '|')
        return (1);
    while (*input)
    {
        if (*input == '\'' && d == 0)
            s = !s;
        else if (*input == '"' && s == 0)
            d = !d;
        if (*input == '|' && s == 0 && d == 0)
        {
            input++;
            while (*input == ' ')
                input++;
            if (*input == '\0' || *input == '|')
                return 1;
        }
        else
            input++;
    }
    return 0;
}