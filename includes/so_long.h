/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:30:33 by shima             #+#    #+#             */
/*   Updated: 2022/08/08 14:08:29 by shima            ###   ########.fr       */
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

# define PLAYER "assets/textures/player.xpm"
# define FLOOR "assets/textures/floor.xpm"
# define WALL "assets/textures/wall.xpm"
# define GOAL "assets/textures/goal.xpm"
# define ITEM "assets/textures/item.xpm"

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define DESTROY_NOTIFY 17

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img_data;

typedef struct	s_game_info {
	void			*mlx_ptr;
	void			*win_ptr;
	char			*map;
	int				map_x;
	int				map_y;
	unsigned int	item_max;
	unsigned int	move_count;
	unsigned int	item_count;
	size_t			player_i;
	t_img_data floor;
	t_img_data player;
	t_img_data goal;
	t_img_data wall;
	t_img_data item;
}	t_game_info;


// gnl
# define BUFFER_SIZE 42
char	*get_next_line(int fd);
char	*strjoin_until_c(char const *s1, char const *s2, char c);
char	*strdup_until_c(const char *s1, char c);
size_t	str_c_len(const char *s, char c);
char	*ft_gnl_strchr(const char *s, int c);
//


#endif