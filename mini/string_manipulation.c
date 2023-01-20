/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:38:41 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/11 17:20:34 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		l;
	int		i;
	char	*str;
	int		p;

	p = !s1;
	if (!s1)
		s1 = ft_strdup("");
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	l = ft_strlen(s1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i <= l)
		str[i] = s1[i];
	i = 0;
	while (l < len)
		str[l++] = s2[i++];
	str[len] = '\0';
	if (p)
		free(s1);
	return (str);
}
