/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:29:40 by amounach          #+#    #+#             */
/*   Updated: 2023/01/03 14:55:44 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(t_tokens **token, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] == ' ')
		i++;
	push_back(token, create_tokens(WSPACE, " "));
	return (i);
}

int	is_pipe(t_tokens **token, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			push_back(token, create_tokens(PIPE, "|"));
		i++;
	}
	return (1);
}

int	is_redin(t_tokens **token, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[i + 1] == '<')
	{
		push_back(token, create_tokens(HEREDOC, "<<"));
		return (2);
	}
	else
		push_back(token, create_tokens(RE_INPUT, "<"));
	return (1);
}

int	is_redout(t_tokens **token, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[i + 1] == '>')
	{
		push_back(token, create_tokens(APPEND, ">>"));
		return (2);
	}
	else
		push_back(token, create_tokens(RE_OUTPUT, ">"));
	return (1);
}
