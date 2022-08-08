/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:14:51 by shima             #+#    #+#             */
/*   Updated: 2022/08/08 21:06:34 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*read_file(t_game_info *game_info);
void	output_image_from_map(t_game_info *game_info);
void	init_map(char *map_path, t_game_info *game_info);
void	get_map_info(t_game_info *game_info);
void	check_map(char *map);
void	check_char(char c);
void	correct_char_num(char *map);
void	is_valid_filename(char *map_path);
void	nl_exist(int fd, bool *is_first_line, char *line, size_t *row_len);
void	nl_not_exist(int fd, char *line, size_t row_len, bool *is_nl);
bool	read_map(t_game_info *game_info, bool *is_first_line, bool *is_nl, size_t *row_len);

// error
void	when_error(int fd, char *error_func_name);
void	map_error(int fd, char *message);
int		exit_program(t_game_info *game_info);

// event
void	event_register(t_game_info *game_info);
int		key_hook(int keycode, t_game_info *param);
void	player_move(t_game_info *game_info, size_t other_i);
int 	loop_hook(t_game_info *param);

int	main(int argc, char *argv[])
{
	t_game_info	game_info;
	
	if (argc != 2)
		exit(EXIT_FAILURE);
	errno = 0;
	ft_bzero(&game_info, sizeof(game_info));
	init_map(argv[1], &game_info);
	event_register(&game_info);
	mlx_loop(game_info.mlx_ptr);
	free(game_info.map);
	return (EXIT_SUCCESS);
}

char	*read_file(t_game_info *game_info)
{
	bool			is_nl;
	bool			is_first_line;
	size_t			row_len;

	is_first_line = true;
	row_len = 0;
	game_info->map = malloc(1 * sizeof(char));
	if (!game_info->map)
		when_error(game_info->fd, "malloc");
	game_info->map[0] = '\0';
	is_nl = true;
	while (read_map(game_info, &is_first_line, &is_nl, &row_len))
		;
	if (errno != 0)
		when_error(game_info->fd, "get_next_line");
	if (is_first_line)
		map_error(game_info->fd, "File may be missing content.\n");
	if (is_nl)
		map_error(game_info->fd, "There may be many line breaks.\n");
	close(game_info->fd);
	return (game_info->map);
}

bool	read_map(t_game_info *game_info, bool *is_first_line, bool *is_nl, size_t *row_len)
{
	char	*line;
	char	*tmp;

	line = get_next_line(game_info->fd);
	if (!line)
		return (false) ;
	if (ft_strchr(line, '\n'))
		nl_exist(game_info->fd, is_first_line, line, row_len);
	else
		nl_not_exist(game_info->fd, line, *row_len, is_nl);
	tmp = game_info->map;
	game_info->map = ft_strjoin(game_info->map, line);
	free(tmp);
	free(line);
	if (!game_info->map)
		when_error(game_info->fd, "ft_strjoin");
	return (true);
}

void	nl_exist(int fd, bool *is_first_line, char *line, size_t *row_len)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	if (*is_first_line)
	{
		while (line[i] != '\n')
		{
			if (line[i] != '1')
				map_error(fd, "The map must be closed by walls.124\n");
			i++;
		}
		*row_len = i;
		*is_first_line = false;
		return ;
	}
	line_len = ft_strlen(line);
	if (*row_len != line_len - 1)
		map_error(fd, "map is not rectangular.132\n");
	if (line[0] != '1' || line[line_len - 2] != '1')
		map_error(fd, "The map must be closed by walls.135\n");
}

void	nl_not_exist(int fd, char *line, size_t row_len, bool *is_nl)
{
	size_t	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			map_error(fd, "The map must be closed by walls.\n");
		i++;
	}
	if (row_len != ft_strlen(line))
		map_error(fd, "map is not rectangular.142\n");
	*is_nl = false;
}

void	init_map(char *map_path, t_game_info *game_info)
{
	is_valid_filename(map_path);
	game_info->fd = open(map_path, O_RDONLY);
	if (game_info->fd == -1)
		when_error(0, "open");
	game_info->map = read_file(game_info);
	// ft_printf("%s", game_info->map);
	correct_char_num(game_info->map);
	get_map_info(game_info);
	game_info->mlx_ptr = mlx_init();
	game_info->win_ptr = mlx_new_window(game_info->mlx_ptr, game_info->map_x * 50, game_info->map_y * 50, "so_long");
	game_info->floor.img = mlx_xpm_file_to_image(game_info->mlx_ptr, FLOOR, &game_info->floor.width, &game_info->floor.height);
	game_info->player.img = mlx_xpm_file_to_image(game_info->mlx_ptr, PLAYER, &game_info->player.width, &game_info->player.height);
	game_info->goal.img = mlx_xpm_file_to_image(game_info->mlx_ptr, GOAL, &game_info->goal.width, &game_info->goal.height);
	game_info->wall.img = mlx_xpm_file_to_image(game_info->mlx_ptr, WALL, &game_info->wall.width, &game_info->wall.height);
	game_info->item.img = mlx_xpm_file_to_image(game_info->mlx_ptr, ITEM, &game_info->item.width, &game_info->item.height);
	output_image_from_map(game_info);
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
			map_error(0, "The characters that can be used are 0 1 C E P.\n");
		i++;
	}
	if (c_count == 0 || e_count == 0 || p_count != 1 || nl_count < 2)
	{
		free(map);
		if (nl_count < 2)
			map_error(0, "map has no more than 3 lines.\n");
		else
			map_error(0, "The map must contain at least 1 E, 1 C, and 1 P.\n");
	}
}

void	map_error(int fd, char *message)
{
	if (fd != 0)
		close(fd);
	ft_printf("Error\n");
	ft_printf("%s", message);
	exit(EXIT_FAILURE);
}

void	is_valid_filename(char *map_path)
{
	char	*str_beginning_with_dot;

	str_beginning_with_dot = ft_strchr(map_path, '.');
	if (!str_beginning_with_dot)
		map_error(0, "The map path must end with \".ber\".\n");
	if (ft_strncmp(str_beginning_with_dot, ".ber\0", 5))
		map_error(0, "The map path must end with \".ber\".\n");
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

void	when_error(int fd, char *error_func_name)
{
	if (fd != 0)
		close(fd);
	perror(error_func_name);
	exit(EXIT_FAILURE);
}

