/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:30:33 by shima             #+#    #+#             */
/*   Updated: 2022/08/08 10:50:44 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>



// gnl
# define BUFFER_SIZE 42
char	*get_next_line(int fd);
char	*strjoin_until_c(char const *s1, char const *s2, char c);
char	*strdup_until_c(const char *s1, char c);
size_t	str_c_len(const char *s, char c);
char	*ft_gnl_strchr(const char *s, int c);
//


#endif