/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:59:20 by shima             #+#    #+#             */
/*   Updated: 2022/08/13 07:28:01 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_file(t_game_info *game)
{
	size_t			row;
	bool			isnl;
	bool			isfirst;

	game->map = malloc(1 * sizeof(char));
	if (!game->map)
		when_error(game->fd, "malloc");
	game->map[0] = '\0';
	row = 0;
	isfirst = true;
	isnl = true;
	while (read_map(game, &isfirst, &isnl, &row))
		;
	if (errno != 0)
		when_error(game->fd, "get_next_line");
	if (isfirst)
		map_error(game->fd, "File may be missing content.\n");
	if (isnl)
		map_error(game->fd, "There may be many line breaks.\n");
	close(game->fd);
}

bool	read_map(t_game_info *game, bool *isfirst, bool *isnl, size_t *row)
{
	char	*line;
	char	*tmp;

	line = get_next_line(game->fd);
	if (!line)
		return (false);
	if (ft_strchr(line, '\n'))
		nl_exist(game->fd, isfirst, line, row);
	else
		nl_not_exist(game->fd, line, *row, isnl);
	tmp = game->map;
	game->map = ft_strjoin(game->map, line);
	free(tmp);
	free(line);
	if (!game->map)
		when_error(game->fd, "ft_strjoin");
	return (true);
}

void	nl_exist(int fd, bool *isfirst, char *line, size_t *row)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	if (*isfirst)
	{
		while (line[i] != '\n')
		{
			if (line[i] != '1')
				map_error(fd, "The map must be closed by walls.\n");
			i++;
		}
		*row = i;
		*isfirst = false;
		return ;
	}
	line_len = ft_strlen(line);
	if (*row != line_len - 1)
		map_error(fd, "map is not rectangular.\n");
	if (line[0] != '1' || line[line_len - 2] != '1')
		map_error(fd, "The map must be closed by walls.\n");
}

void	nl_not_exist(int fd, char *line, size_t row, bool *isnl)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			map_error(fd, "The map must be closed by walls.\n");
		i++;
	}
	if (row != i)
		map_error(fd, "map is not rectangular.\n");
	*isnl = false;
}

void	get_map_info(t_game_info *game)
{
	size_t	i;

	i = 0;
	while (game->map[i] != '\n')
	{
		game->map_x++;
		i++;
	}
	i = 0;
	while (game->map[i])
	{
		if (game->map[i] == 'C')
			game->item_max++;
		if (game->map[i] == 'P')
			game->player_i = i;
		if (game->map[i] == '\n')
			game->map_y++;
		i++;
	}
	game->map_y++;
}
