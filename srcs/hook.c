/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:11:26 by shima             #+#    #+#             */
/*   Updated: 2022/08/09 14:31:27 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	event_register(t_game_info *game)
{
	mlx_key_hook(game->win_ptr, &key_hook, game);
	mlx_hook(game->win_ptr, DESTROY_NOTIFY, 1L << 17, &exit_hook, game);
	mlx_loop_hook(game->mlx_ptr, &loop_hook, game);
}

int	key_hook(int keycode, t_game_info *game)
{
	size_t	other_i;

	other_i = 0;
	if (keycode == KEY_ESC)
		exit_hook(game);
	else if (keycode == KEY_W)
		other_i = game->player_i - (game->map_x + 1);
	else if (keycode == KEY_A)
		other_i = game->player_i - 1;
	else if (keycode == KEY_S)
		other_i = game->player_i + (game->map_x + 1);
	else if (keycode == KEY_D)
		other_i = game->player_i + 1;
	else
		return (0);
	player_move(game, other_i);
	return (0);
}

void	player_move(t_game_info *game, size_t other_i)
{
	if (game->map[other_i] == '0' || game->map[other_i] == 'C')
	{
		if (game->map[other_i] == 'C')
			game->item_count++;
		game->map[other_i] = 'P';
		game->map[game->player_i] = '0';
		game->player_i = other_i;
		game->move_count++;
		ft_printf("%u\n", game->move_count);
	}
	if (game->map[other_i] == 'E' && game->item_count == game->item_max)
		exit_hook(game);
}

int	loop_hook(t_game_info *game)
{
	output_image_from_map(game);
	return (0);
}

int	exit_hook(t_game_info *game)
{
	free(game->map);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(EXIT_SUCCESS);
}
