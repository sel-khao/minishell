#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"



int validate_input(const char *input)
{
    if (!input[0] || !input)
        return (1);//error
    if (quote(input) == 1);
        return (1);
    if (validate_pipe(input) == 1)
        return (1);
    return (0);
}

void tokenize(t_shell *shell)
{
    if (!validate_input(shell->input))
        return ;
    
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_shell shell;

    shell.tokens = NULL;
    shell.input = NULL;
    shell.cmds = NULL;
    while (1)
    {
        ft_readline(&shell);
        tokenize(&shell);
        free(shell.input);
        shell.input = NULL;
    }
    return 0;
}
