/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:20:21 by shima             #+#    #+#             */
/*   Updated: 2022/08/09 14:51:56 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_valid_filename(char *map_path)
{
	char	*str_beginning_with_dot;

	str_beginning_with_dot = ft_strchr(map_path, '.');
	if (!str_beginning_with_dot
		|| ft_strncmp(str_beginning_with_dot, ".ber\0", 5))
		map_error(0, "The map path must end with \".ber\".\n");
}

void	correct_char_num(char *map)
{
	size_t			i;
	t_char_count	cc;

	i = 0;
	ft_bzero(&cc, sizeof(cc));
	while (map[i])
	{
		count_char(&cc, map[i]);
		i++;
	}
	if (cc.nl_count < 2)
		map_error(0, "map has no more than 3 lines.\n");
	if (cc.c_count <= 0 || cc.e_count <= 0 || cc.p_count != 1)
		map_error(0, "The map must contain at least 1 E, 1 C, and 1 P.\n");
}

void	count_char(t_char_count *cc, char c)
{
	if (c == 'C')
		cc->c_count++;
	else if (c == 'E')
		cc->e_count++;
	else if (c == 'P')
		cc->p_count++;
	else if (c == '\n')
		cc->nl_count++;
	else if (c == '1' || c == '0')
		(void)c;
	else
		map_error(0, "The characters that can be used are 0 1 C E P.\n");
}
