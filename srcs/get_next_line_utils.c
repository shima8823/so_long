/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:31:54 by shima             #+#    #+#             */
/*   Updated: 2022/08/15 10:58:50 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*strjoin_until_c(char const *s1, char const *s2, char c);
char	*strdup_until_c(const char *s1, char c);
size_t	str_c_len(const char *s, char c);
char	*ft_gnl_strchr(const char *s, int c);

char	*ft_gnl_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*strjoin_until_c(char const *s1, char const *s2, char c)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s1 || !s2 || (s1[0] == '\0' && s2[0] == '\0'))
		return (NULL);
	s1_len = str_c_len(s1, c);
	s2_len = str_c_len(s2, c);
	result = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = 0;
	while (s2[i])
	{
		result[s1_len + i] = s2[i];
		i++;
		if (s2[i - 1] == c)
			break ;
	}
	result[s1_len + i] = '\0';
	return (result);
}

char	*strdup_until_c(const char *s1, char c)
{
	size_t	len;
	char	*dst;
	size_t	i;

	len = str_c_len(s1, c);
	dst = malloc(len + 1 * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
		if (s1[i - 1] == c)
			break ;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	str_c_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i])
		i++;
	return (i);
}
