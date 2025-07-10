/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:15:24 by sel-khao          #+#    #+#             */
/*   Updated: 2025/07/10 12:31:36 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**add_word(char **argv, char *word)
{
	int		i;
	int		j;
	char	**av;

	i = 0;
	j = 0;
	if (argv)
	{
		while (argv[i])
			i++;
	}
	av = malloc(sizeof(char *) * (i + 2));
	if (!av)
		return (NULL);
	while (j < i)
	{
		av[j] = argv[j];
		j++;
	}
	av[i] = ft_strdup(word);
	av[i + 1] = NULL;
	free(argv);
	return (av);
}

char	*extract_token(const char *input, int start, int end)
{
	char	*out;
	int		i;
	int		j;

	i = start;
	j = 0;
	out = malloc(end - start + 1);
	while (i < end)
		out[j++] = input[i++];
	out[j] = '\0';
	return (out);
}

void	tokenize(t_shell *shell)
{
	int		i;
	char	*input;
	int		start;
	char	*no_quote;
	char	*word;
	char	quote_type;

	i = 0;
	input = shell->input;
	while (input[i] && is_space(input[i]))
		i++;
	while (input[i])
	{
		if (is_special(input[i]))
			handle_special(shell, input, &i);
		else if (is_word(input[i]))
		{
			start = i;
			while (input[i] && (is_word(input[i]) || in_quotes(input, i)))
				i++;
			word = ft_substr(input, start, i - start);
			quote_type = 0;
			if (strchr(word, '\''))
				quote_type = '\'';
			else if (strchr(word, '"'))
				quote_type = '"';
			no_quote = process_quotes(word);
			add_token(shell, no_quote, WORD, quote_type);
			free(word);
			free(no_quote);
		}
		while (input[i] && is_space(input[i]))
			i++;
	}
}

void	tok_cmd(t_shell *shell, char **envp)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	*tmp;
	t_token	*prev;

	tmp = shell->tokens;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	init(cmd);
	head = cmd;
	shell->cmds = cmd;
	while (tmp)
	{
		prev = tmp;
		if (tmp->type == HEREDOC)
			check_delim(&tmp, envp, cmd, &shell->es);
		else if (tmp->type == PIPE)
			check_type2(&tmp, &cmd);
		else
			check_type(&tmp, cmd, envp, &shell->es);
		if (tmp == prev)
			tmp = tmp->next;
	}
	shell->cmds = head;
}
