/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:13:04 by sara              #+#    #+#             */
/*   Updated: 2025/05/19 23:07:58 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int validate_redirection(char *input)
{
    int i;
    int c = 0;
    
    i = 0;
    if (input[0] == '<' || input[0] == '>')
        return (1);
    while (input[i])
    {
        c = 0;
        while (input[i] == '<' || input[i] == '>')
        {
            c++;
            if (c > 2)
                return 1;
            i++;
        }
        if ((input[i] == '<' && input[i + 1] == '>') ||
            (input[i] == '>' && input[i + 1] == '<'))
           return (1);
        if ((input[i] == '<' || input[i] == '>') && input[i + 1] == '\0')
            return (1);
        i++;
    }
    return 0;
}

int validate_quote(char *str)
{//am i inside or outisde quotes?
    int i = 0;
    int d = 0;//outside it
    int s = 0;

    while (str[i])
    {
        if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '"'))
            i++;
        else
        {
            if (str[i] == '\'' && d == 0)//
                s = !s;//alterna s tra 1 e 0, on and off, in and out
            else if (str[i] == '"' && s == 0)
                d = !d;
        }
        i++;
    }
    if (s == 1 || d == 1)
        return (1);//unclosed quotes
    return (0);//success
}

int validate_pipe(char *input)
{
    int s = 0;
    int d = 0;

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

void ft_readline(t_shell *shell)
{
    shell->input = readline("mininshell>");
    if (!shell->input)
        exit(0);
    if (shell->input[0])
        add_history(shell->input);
}

int validate_input(char *input)
{
    if (!input || !input[0])
        return (1);//error
    while (*input == ' ')
        input++;
    if (quote(input) == 1)
        return (1);
    if (validate_pipe(input) == 1)
        return (1);
    if (validate_redirections(input) == 1)
        return (1);
    return (0);
}

void tokenize(t_shell *shell)
{
    if (validate_input(shell->input))
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
