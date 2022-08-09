/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:18:35 by shima             #+#    #+#             */
/*   Updated: 2022/08/09 13:22:55 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error(int fd, char *message)
{
	if (fd != 0)
		close(fd);
	ft_printf("Error\n");
	ft_printf("%s", message);
	exit(EXIT_FAILURE);
}

void	when_error(int fd, char *error_func_name)
{
	if (fd != 0)
		close(fd);
	perror(error_func_name);
	exit(EXIT_FAILURE);
}
