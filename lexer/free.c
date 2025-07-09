/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sara <sara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:07:09 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/09 01:58:26 by sara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_argv(char **argv)
{
    int i = 0;
    
    if (!argv)
        return;
    
    printf("DEBUG: free_argv called, argv = %p\n", argv);
    while (argv[i])
    {
        printf("DEBUG: freeing argv[%d] = '%s'\n", i, argv[i]);
        free(argv[i]);
        i++;
    }
    free(argv);
    printf("DEBUG: free_argv completed\n");
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->filename);
		free(tmp);
	}
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_all(t_shell *shell)
{
    if (shell->input)
    {
        free(shell->input);
        shell->input = NULL;
    }
    if (shell->tokens)
    {
        free_tokens(shell->tokens);
        shell->tokens = NULL;
    }
    if (shell->cmds)
    {
        free_cmds(shell->cmds);
        shell->cmds = NULL;
    }
}

void free_cmds(t_cmd *cmds)
{
    t_cmd *tmp;
    
    printf("DEBUG: free_cmds called\n");
    while (cmds)
    {
        tmp = cmds;
        cmds = cmds->next;
        printf("DEBUG: freeing cmd, argv = %p\n", tmp->argv);
        if (tmp->argv)
            free_argv(tmp->argv);
        if (tmp->redir)
            free_redir(tmp->redir);
        free(tmp);
    }
    printf("DEBUG: free_cmds completed\n");
}
