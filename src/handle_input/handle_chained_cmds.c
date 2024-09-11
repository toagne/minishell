/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chained_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:38:55 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/11 19:19:19 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_subcmd(t_shell *shell)
{
	int i;
	int	paren_count;
	char *sub_cmd;
	
	sub_cmd = NULL;
	i = 0;
	paren_count = 1;
	while (shell->input[i] && shell->input[i] != '(')
		i++;
	while (shell->input[++i])
	{
		if (shell->input[i] == '(')
			paren_count++;
		else if (shell->input[i] == ')')
			paren_count--;
		if (!paren_count)
			break ;
		sub_cmd = append_char(sub_cmd, shell->input[i]);	
	}
	free(shell->input);
	shell->input = sub_cmd;
}

static void	preserve_remaining_cmds(t_shell *shell, int i)
{
	int j;
	int k;

	shell->tmp_chained_cmds = malloc(sizeof(char *) * (shell->chain_count + 2));
	shell->tmp_chained_tokens = malloc(sizeof(char *) * (shell->chain_count + 2));
	init_arr(shell->tmp_chained_cmds, (shell->chain_count + 2));
	init_arr(shell->tmp_chained_tokens, (shell->chain_count + 2));
	j = i + 1;
	k = 0;
	while (shell->chained_cmds[j])
	{
		shell->tmp_chained_cmds[k] = ft_strdup(shell->chained_cmds[j]);
		if (shell->chained_tokens[j -1])
			shell->tmp_chained_tokens[k] = ft_strdup(shell->chained_tokens[j - 1]);
		j++;
		k++;
	}
	free_arr(shell->chained_cmds);
	free_arr(shell->chained_tokens);
}

static void handle_subcommand(t_shell *shell, int *i)
{
	shell->in_subcmd++;
	parse_subcmd(shell);
	if (shell->chained_cmds[*i + 1])
	{
		preserve_remaining_cmds(shell, *i);
		handle_input(shell);
		free_arr(shell->chained_cmds);
		free_arr(shell->chained_tokens);
		shell->chained_cmds = shell->tmp_chained_cmds;
		shell->chained_tokens = shell->tmp_chained_tokens;
		shell->in_subcmd--;
		handle_chained_cmds(shell);
	}
	else
	{
		free_arr(shell->chained_cmds);
		free_arr(shell->chained_tokens);
		handle_input(shell);
		free_arr(shell->chained_cmds);
		free_arr(shell->chained_tokens);
		shell->in_subcmd--;
	}
}

static void	clean_chained_cmds(t_shell *shell)
{
	if (shell->in_subcmd)
		return ;
	free_arr(shell->chained_cmds);
	free_arr(shell->chained_tokens);
	shell->chain_count = 0;
}

void handle_chained_cmds(t_shell *shell)
{
	int i;

	i = -1;
	while (shell->chained_cmds[++i])
	{
		shell->input = ft_strdup(shell->chained_cmds[i]);
		if (ft_strchr(shell->input, '('))
		{
			handle_subcommand(shell, &i);
			return ;
		}
		else
			handle_input(shell);
		if (shell->chained_tokens[i] && strcmp(shell->chained_tokens[i], "&&") == 0 && shell->retval != 0)
		{
			i += 2;
			continue;
		}
		else if (shell->chained_tokens[i] && strcmp(shell->chained_tokens[i], "||") == 0 && shell->retval == 0)
		{
			i += 2;
			continue;
		}
	}
	clean_chained_cmds(shell);
}
