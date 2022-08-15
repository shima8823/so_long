/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:14:51 by shima             #+#    #+#             */
/*   Updated: 2022/08/12 21:58:04 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_map(char *map_path, t_game_info *game);
static void	setting_mlx(t_game_info *game);
static void	draw_image(t_game_info *game, int *x, int *y, char c);
void		output_image_from_map(t_game_info *game);

int	main(int argc, char *argv[])
{
	t_game_info	game;

	if (argc != 2)
		exit(EXIT_FAILURE);
	errno = 0;
	ft_bzero(&game, sizeof(game));
	init_map(argv[1], &game);
	event_register(&game);
	mlx_loop(game.mlx_ptr);
	free(game.map);
	exit(EXIT_SUCCESS);
}

static void	init_map(char *map_path, t_game_info *game)
{
	check_filename(map_path, game);
	read_file(game);
	correct_char_num(game->map);
	get_map_info(game);
	setting_mlx(game);
	output_image_from_map(game);
}

static void	setting_mlx(t_game_info *game)
{
	game->mlx_ptr = mlx_init();
	if (!(game->mlx_ptr))
		when_error(0, "mlx_init");
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->map_x * 50, game->map_y * 50, "so_long");
	if (!(game->win_ptr))
		when_error(0, "mlx_new_window");
	game->floor.img = mlx_xpm_file_to_image(game->mlx_ptr,
			FLOOR, &game->floor.width, &game->floor.height);
	game->player.img = mlx_xpm_file_to_image(game->mlx_ptr,
			PLAYER, &game->player.width, &game->player.height);
	game->goal.img = mlx_xpm_file_to_image(game->mlx_ptr,
			GOAL, &game->goal.width, &game->goal.height);
	game->wall.img = mlx_xpm_file_to_image(game->mlx_ptr,
			WALL, &game->wall.width, &game->wall.height);
	game->item.img = mlx_xpm_file_to_image(game->mlx_ptr,
			ITEM, &game->item.width, &game->item.height);
}

void	output_image_from_map(t_game_info *game)
{
	size_t	i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	while ((game->map)[i])
	{
		draw_image(game, &x, &y, (game->map)[i]);
		i++;
	}
}

static void	draw_image(t_game_info *game, int *x, int *y, char c)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx_ptr,
			game->win_ptr, game->wall.img, *x, *y);
	else if (c == '0')
		mlx_put_image_to_window(game->mlx_ptr,
			game->win_ptr, game->floor.img, *x, *y);
	else if (c == 'C')
		mlx_put_image_to_window(game->mlx_ptr,
			game->win_ptr, game->item.img, *x, *y);
	else if (c == 'E')
		mlx_put_image_to_window(game->mlx_ptr,
			game->win_ptr, game->goal.img, *x, *y);
	else if (c == 'P')
		mlx_put_image_to_window(game->mlx_ptr,
			game->win_ptr, game->player.img, *x, *y);
	else if (c == '\n')
	{
		*y += 50;
		*x = 0;
		return ;
	}
	*x += 50;
}
