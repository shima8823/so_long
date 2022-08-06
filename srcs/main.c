/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:14:51 by shima             #+#    #+#             */
/*   Updated: 2022/08/06 14:42:10 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

# define PLAYER "assets/textures/player.xpm"
# define FLOOR "assets/textures/floor.xpm"
# define WALL "assets/textures/wall.xpm"
# define GOAL "assets/textures/goal.xpm"
# define ITEM "assets/textures/item.xpm"

typedef struct	s_vars {
	void	*mlx_ptr;
	void	*win_ptr;
	char	*map;
}	t_game_info;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img_data;

void	init_map(char *map_path, t_game_info *game_info);

int	main(int argc, char *argv[])
{
	t_game_info    game_info;
	t_img_data    floor;
	t_img_data    player;
	t_img_data    goal;
	t_img_data    wall;
	t_img_data    item;

	if (argc != 2)
		exit(EXIT_SUCCESS);


	init_map(argv[1], &game_info);

	// var. = mlx_init();
	// var.win = mlx_new_window(var.mlx, 500, 500, "so_long");
	
	// floor.img = mlx_xpm_file_to_image(var.mlx, FLOOR, &floor.width, &floor.height);
	// floor.addr = mlx_get_data_addr(floor.img, &floor.bits_per_pixel, &floor.line_length, &floor.endian);
	// mlx_put_image_to_window(var.mlx, var.win, floor.img, 0, 0);
	// mlx_loop(var.mlx);
}

void	init_map(char *map_path, t_game_info *game_info)
{
	int		fd;
	char	buf[1024];
	ssize_t	len;

	game_info->map = malloc(1);
	game_info->map[0] = '\0';
	
	fd = open(map_path, O_RDONLY);

	while (true)
	{
		len = read(fd, buf, 1024);
		if (len < 0)
			exit(EXIT_FAILURE);
		buf[len] = '\0';
		if (len == 0)
			break;
		game_info->map = ft_strjoin(game_info->map, buf);
	}
	printf("gamemap:\n%s", game_info->map);
}