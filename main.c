/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 07:47:10 by sel-khao          #+#    #+#             */
/*   Updated: 2025/05/20 10:37:41 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


void free_all(t_shell *shell)
{
    if (shell->input)
    {
        free(shell->input);
        shell->input = NULL;
    }
    clear_history();
}

void ft_readline(t_shell *shell)
{
    shell->input = readline("mininshell> ");
    if (!shell->input)
    {
        free_all(shell);
        exit(0);
    }
    if (shell->input[0])
        add_history(shell->input);
}

void tokenize(t_shell *shell)
{
    if (validate_input(shell->input))
    {
        printf("Invalid input: %s\n", shell->input);
        return ;
    }
    printf("Valid input: %s\n", shell->input);
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
        if (!shell.input)
            free_all(&shell);
        tokenize(&shell);
        free(shell.input);
        shell.input = NULL;
    }
    return 0;
}
