/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:06:45 by sel-khao          #+#    #+#             */
/*   Updated: 2025/05/03 13:11:49 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int i = 0;
	
	while (str[i])
		i++;
	return (i);
}

char	*quoted(char *line)
{
	int		i;
	int		j;
	char	*arg;
	int		len;

	j = 0;
	i = 0;
	len = ft_strlen(line);
	arg = malloc(sizeof(char) * len + 1);
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				arg[j++] = line[i++];
		}
		i++;
	}
	arg[j] = '\0';
	return (arg);
}

int	main(int argc, char **argv)
{
	(void)argc;
	char *result = quoted(argv[1]);
	printf("%s\n", result);
	free(result);
}
