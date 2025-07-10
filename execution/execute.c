/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-khao <sel-khao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:20 by kbossio           #+#    #+#             */
/*   Updated: 2025/07/10 15:41:51 by sel-khao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_overflow(char *str, long long *result)
{
	int					i;
	int					sign;
	unsigned long long	num;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		if ((num > LLONG_MAX && sign == 1) || (num > LLONG_MIN && sign == -1))
			return (0);
		i++;
	}
	*result = (long long)num * sign;
	return (1);
}

int	exit_shell(int status, t_shell *shell, char **envp, char **str, t_cmd *tmp)
{
	long long	status_code;
	int			fd;

	status_code = status;
	fd = 0;
	if (str && str[0])
	{
		printf("exit\n");
		if (str[1])
			return (write(2, "bash: exit: too many arguments\n", 31), 1);
		if (check_overflow(str[0], &status_code) == 0)
		{
			write(2, "bash: exit: ", 12);
			write(2, str[0], ft_strlen(str[0]));
			write(2, ": numeric argument required\n", 28);
			status_code = 2;
		}
		else
			status_code = status_code % 256;
	}
	if (envp)
		free_arr(envp, NULL);
	rl_clear_history();
	if (tmp != NULL)
		shell->cmds = tmp;
	if (shell)
		free_all(shell);
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	exit(status_code);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

char	**execute(t_shell *shell, char **cmd, char *envp[], t_cmd *tmp)
{
	t_fd	f;

	f.input = dup(STDIN_FILENO);
	f.output = dup(STDOUT_FILENO);
	if (handle_redirections(shell->cmds))
	{
		restore_fds(f.input, f.output);
		return (envp);
	}
	if (is_builtin(cmd[0]) == 1)
		g_status = 0;
	if (ft_strcmp(cmd[0], "cd") == 0)
		shell->es = cd(cmd + 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		shell->es = pwd();
	else if (ft_strcmp(cmd[0], "echo") == 0)
		shell->es = ft_echo(cmd + 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		shell->es = env(envp);
	else if (ft_strcmp(cmd[0], "export") == 0)
		envp = export(envp, cmd + 1, &shell->es);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		shell->es = unset(cmd + 1, envp);
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		restore_fds(f.input, f.output);
		rl_clear_history();
		shell->es = exit_shell(shell->es, shell, envp, cmd + 1, tmp);
	}
	else
		shell->es = exec_external(shell, shell->cmds->argv, envp, &f);
	restore_fds(f.input, f.output);
	return (envp);
}

void	restore_fds(int in, int out)
{
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(in);
	close(out);
}
