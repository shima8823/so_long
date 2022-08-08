/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:14:51 by shima             #+#    #+#             */
/*   Updated: 2022/08/08 11:55:57 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

char	*read_file(char *map_path);
void	when_error(char *error_func_name);
void	output_image_from_map(t_game_info *game_info);
void	init_map(char *map_path, t_game_info *game_info);
void	get_map_info(t_game_info *game_info);
int		exit_program(t_game_info *game_info);
void	check_map(char *map);
void	map_error();
void	check_char(char c);
void	correct_char_num(char *map);


// event
void	event_register(t_game_info *game_info);
int		key_hook(int keycode, t_game_info *param);
void	player_move(t_game_info *game_info, size_t other_i);

int 	loop_hook(t_game_info *param);


int	main(int argc, char *argv[])
{
	t_game_info	game_info;
	
	if (argc != 2)
		exit(EXIT_SUCCESS);
	errno = 0;
	ft_bzero(&game_info, sizeof(game_info));
	init_map(argv[1], &game_info);
	event_register(&game_info);
	mlx_loop(game_info.mlx_ptr);
	free(game_info.map);
}

char	*read_file(char *map_path)
{
	int		fd;
	char	*result;
	char	*tmp;
	int		nl_count;
	size_t	row_len;
	char	*gnl_ret;

	result = malloc(1);
	result[0] = '\0';
	nl_count = 0;
	
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		when_error("open");

	result = get_next_line(fd);
	if (!result)
		map_error("Nothing in the file.\n");
	if (ft_strchr(result, '\n'))
	{
		nl_count++;
		row_len = ft_strlen(result) - 1;
	}
	while (true)
	{
		gnl_ret = get_next_line(fd);
		if (!gnl_ret)
			break;
		if (ft_strchr(gnl_ret, '\n'))
		{
			nl_count++;
			if (row_len != ft_strlen(gnl_ret) - 1)
				map_error("map is not rectangular.\n");
		}
		else 
			if (row_len != ft_strlen(gnl_ret))
				map_error("map is not rectangular.\n");
		tmp = result;
		result = ft_strjoin(result, gnl_ret);
		if (result == NULL)
			when_error("ft_strjoin");
		free(tmp);
		free(gnl_ret);
	}
	close(fd);
	if (nl_count < 2)
		map_error("map has no more than 3 lines.\n");
	return (result);
}

void	init_map(char *map_path, t_game_info *game_info)
{
	game_info->map = read_file(map_path);
	ft_printf("%s", game_info->map);
	check_map(game_info->map);
	get_map_info(game_info);
	
	game_info->mlx_ptr = mlx_init();
	game_info->win_ptr = mlx_new_window(game_info->mlx_ptr, game_info->map_x * 50, game_info->map_y * 50, "so_long");

	game_info->floor.img = mlx_xpm_file_to_image(game_info->mlx_ptr, FLOOR, &game_info->floor.width, &game_info->floor.height);
	game_info->player.img = mlx_xpm_file_to_image(game_info->mlx_ptr, PLAYER, &game_info->player.width, &game_info->player.height);
	game_info->goal.img = mlx_xpm_file_to_image(game_info->mlx_ptr, GOAL, &game_info->goal.width, &game_info->goal.height);
	game_info->wall.img = mlx_xpm_file_to_image(game_info->mlx_ptr, WALL, &game_info->wall.width, &game_info->wall.height);
	game_info->item.img = mlx_xpm_file_to_image(game_info->mlx_ptr, ITEM, &game_info->item.width, &game_info->item.height);
	output_image_from_map(game_info);

	// floor.addr = mlx_get_data_addr(floor.img, &floor.bits_per_pixel, &floor.line_length, &floor.endian);
	// mlx_put_image_to_window(game_info->mlx_ptr, game_info->win_ptr, floor.img, 0, 0);
	// mlx_put_image_to_window(game_info->mlx_ptr, game_info->win_ptr, floor.img, 25, 0);

}

void	output_image_from_map(t_game_info *game_info)
{
	size_t	i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	while ((game_info->map)[i])
	{
		if ((game_info->map)[i] == '1')
			mlx_put_image_to_window(game_info->mlx_ptr, game_info->win_ptr, game_info->wall.img, x, y);
		else if ((game_info->map)[i] == '0')
			mlx_put_image_to_window(game_info->mlx_ptr, game_info->win_ptr, game_info->floor.img, x, y);
		else if ((game_info->map)[i] == 'C')
			mlx_put_image_to_window(game_info->mlx_ptr, game_info->win_ptr, game_info->item.img, x, y);
		else if ((game_info->map)[i] == 'E')
			mlx_put_image_to_window(game_info->mlx_ptr, game_info->win_ptr, game_info->goal.img, x, y);
		else if ((game_info->map)[i] == 'P')
			mlx_put_image_to_window(game_info->mlx_ptr, game_info->win_ptr, game_info->player.img, x, y);
		else if ((game_info->map)[i] == '\n')
		{
			y += 50;
			x = 0;
			i++;
			continue ;
		}
		x += 50;
		i++;
	}
}

void	get_map_info(t_game_info *game_info)
{
	size_t	i;

	i = 0;
	while (game_info->map[i] && game_info->map[i] != '\n')
	{
		game_info->map_x++;
		i++;
	}
	i = 0;
	while (game_info->map[i])
	{
		if (game_info->map[i] == 'C')
			game_info->item_max++;
		if (game_info->map[i] == 'P')
			game_info->player_i = i;
		if (game_info->map[i] == '\n')
			game_info->map_y++;
		i++;
	}
	game_info->map_y++;
	
}

void	check_map(char *map)
{
	correct_char_num(map);

}

void	correct_char_num(char *map)
{
	size_t			i;
	unsigned int	c_count;
	unsigned int	e_count;
	unsigned int	p_count;
	unsigned int	nl_count;

	i = 0;
	c_count = 0;
	e_count = 0;
	p_count = 0;
	nl_count = 0;
	while (map[i])
	{
		if (map[i] == 'C')
			c_count++;
		else if (map[i] == 'E')
			e_count++;
		else if (map[i] == 'P')
			p_count++;
		else if (map[i] == '\n')
			nl_count++;
		else if (map[i] == '1' || map[i] == '0')
			(void)i;
		else
			map_error();
		i++;
	}
	if (c_count == 0 || e_count == 0 || p_count != 1 || nl_count < 2)
	{
		free(map);
		map_error("The map must contain at least 1 E, 1 C, and 1 P.\n");
	}
}

void	check_char(char c)
{
	char	*s;
	size_t	i;
	bool	is_in;

	s = "10CEP\n";
	i = 0;
	is_in = false;
	while (s[i])
	{
		if (c == s[i])
			is_in = true;
		i++;
	}
	if (!is_in)
		map_error();
}

bool	is_rectangle(char *map)
{
	int		nl_count;
	size_t	i;
	size_t	first_row_x;

	i = 0;
	nl_count = 0;
	while (map[i] != '\n')
		i++;
	first_row_x = i - 1;
	i++;
	// while ()
	while (map[i] && map[i] != '\n')
		;

}

bool	is_wall_around(char *map)
{
	size_t	i;

	i = 0;
	while (map[i] && map[i] != '\n')
	{
		if (map[i] != '1')
			return (false);
		i++;
	}
	if (map[i] && map[i + 1] && map[i + 1] != '1')
		return (false);
	while (map[i] && map[i] != '\n')
		i++;
	if (map[i] && map[i + 1] && map[i + 1] != '1')
		return (false);
}

void	map_error(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s", message);
	exit(EXIT_FAILURE);
}

// event系
void	event_register(t_game_info *game_info)
{
	mlx_key_hook(game_info->win_ptr, &key_hook, game_info);
	mlx_hook(game_info->win_ptr, DESTROY_NOTIFY, 1L << 17, &exit_program, game_info);
	mlx_loop_hook(game_info->mlx_ptr, &loop_hook, game_info);
}

int	key_hook(int keycode, t_game_info *game_info)
{
	size_t	other_i;
	
	if (keycode == KEY_ESC)
		exit_program(game_info);
	else if (keycode == KEY_W)
		other_i = game_info->player_i - (game_info->map_x + 1);
	else if (keycode == KEY_A)
		other_i = game_info->player_i - 1;
	else if (keycode == KEY_S)
		other_i = game_info->player_i + (game_info->map_x + 1);
	else if (keycode == KEY_D)
		other_i = game_info->player_i + 1;
	else
		return (0);
	player_move(game_info, other_i);
	return (0);
}

void	player_move(t_game_info *game_info, size_t other_i)
{
	if (game_info->map[other_i] == '0' || game_info->map[other_i] == 'C')
	{
		if (game_info->map[other_i] == 'C')
			game_info->item_count++;
		game_info->map[other_i] = 'P';
		game_info->map[game_info->player_i] = '0';
		game_info->player_i = other_i;
		game_info->move_count++;
		ft_printf("%u\n", game_info->move_count);
	}
	if (game_info->map[other_i] == 'E' && game_info->item_count == game_info->item_max)
		exit_program(game_info);
}

int loop_hook(t_game_info *param)
{
	output_image_from_map(param);
	return (0);
}

int	exit_program(t_game_info *game_info)
{
	free(game_info->map);
	mlx_destroy_window(game_info->mlx_ptr, game_info->win_ptr);
	exit(EXIT_SUCCESS);
}

void	when_error(char *error_func_name)
{
	perror(error_func_name);
	exit(EXIT_FAILURE);
}

