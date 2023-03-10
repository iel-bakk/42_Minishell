/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:11:44 by amounach          #+#    #+#             */
/*   Updated: 2023/01/11 17:22:44 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	match_variables(t_env **env, char **str)
{
	int		i;
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	i = 1;
	while (str[i])
	{
		tmp = *env;
		while (tmp)
		{
			next = tmp->next;
			if (ft_strcmp(str[i], tmp->v_name) == 0)
				delete_onev(env, tmp);
			tmp = next;
		}
		i++;
	}
}

void	unset(t_env **env, char **str)
{
	match_variables(env, str);
}
