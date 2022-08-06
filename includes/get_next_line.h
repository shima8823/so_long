/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:29:04 by shima             #+#    #+#             */
/*   Updated: 2022/06/13 12:30:02 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

char	*get_next_line(int fd);
char	*strjoin_until_c(char const *s1, char const *s2, char c);
char	*strdup_until_c(const char *s1, char c);
size_t	str_c_len(const char *s, char c);
char	*ft_strchr(const char *s, int c);

#endif