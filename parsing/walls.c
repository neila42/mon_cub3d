/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/12/27 17:31:02 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	player_pos(int x, int y, t_data *data)
{
	if (data->player_x != 0 || data->player_y != 0)
		fail("Multiple start position for player");
	data->player_x = x;
	data->player_y = y;
	data->player_orientation = data->map[y][x];
	data->map[y][x] = '0';
	return (0);
}

// check vertical et horizontal, en croix 
// je rentre seulement dans le check quand je suis le sol 
int	cross_check(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->y_lenm)
	{
		x = 0;
		while (x < data->x_lenm)
		{
			if (data->map[y][x] == '0')
			{
				if (y == 0 || y == data->y_lenm - 1
					|| x == 0 || x == data->x_lenm - 1
					|| data->map[y][x - 1] == ' '
					|| data->map[y][x + 1] == ' '
					|| data->map[y - 1][x] == ' '
					|| data->map[y + 1][x] == ' ')
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_walls(t_data *data)
{
	int		x;
	int		y;
	char	i_char;

	data->player_x = 0;
	data->player_y = 0;
	data->player_orientation = NORTH;
	y = 0;
	while (y < data->y_lenm)
	{
		x = 0;
		while (x < data->x_lenm)
		{
			i_char = data->map[y][x];
			if (i_char == 'N' || i_char == 'S'
				|| i_char == 'W' || i_char == 'E')
				player_pos(x, y, data);
			x++;
		}
		y++;
	}
	if (cross_check(data) == -1)
	{
		fail("Not enough walls (cross_check)");
		return (-1);
	}
	return (0);
}
