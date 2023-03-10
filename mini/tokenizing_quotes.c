/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:49:54 by amounach          #+#    #+#             */
/*   Updated: 2023/01/08 04:29:42 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*inside_double_quote(char *line, int *i)
{
	int		len;
	char	*tmp;

	len = 0;
	while (line[*i + len] != '"' && line[*i + len])
		len++;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	ft_strlcpy(tmp, line + *i, len + 1);
	*i += len;
	return (tmp);
}

char	*inside_single_quote(char *line, int *i)
{
	int		len;
	char	*tmp;

	len = 0;
	while (line[*i + len] != '\'' && line[*i + len])
		len++;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	ft_strlcpy(tmp, line + *i, len + 1);
	*i += len;
	return (tmp);
}

t_tokens	*get_special(char *line, int *i)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (line[*i] == '|')
		tmp = get_pipe(i);
	else if (line[*i] == '>')
		tmp = get_right_out(line, i);
	else if (line[*i] == '<')
		tmp = get_left_out(line, i);
	else if (line[*i] == '"')
		tmp = get_double_quote(line, i);
	else if (line[*i] == '\'')
		tmp = get_single_quote(line, i);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*allocat_word(char *line, int *i)
{
	int		len;
	char	*word;

	len = 0;
	while (line[*i + len] && !is_special(line[*i + len]) && line[*i
			+ len] != '$')
		len++;
	word = (char *)malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, line + *i, len + 1);
	*i += len;
	return (word);
}

t_tokens	*get_word(char *line, int *i)
{
	char		*word;
	t_tokens	*w_token;

	if (!line)
		return (NULL);
	if (line[*i] == '$' && line[*i + 1])
	{
		w_token = create_tokens(VARIABLE, "");
		*i += 1;
	}
	else if (line[*i] == '$')
		return ((*i)++, create_tokens(WORD, "$"));
	else
		w_token = create_tokens(WORD, "");
	free(w_token->value);
	word = allocat_word(line, i);
	if (!word)
		return (NULL);
	w_token->value = word;
	if (!w_token)
		return (NULL);
	return (w_token);
}
