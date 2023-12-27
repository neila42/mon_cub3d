/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/12/27 17:33:06 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	reverse_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i1;
	size_t	i2;

	i1 = ft_strlen(s1) - 1;
	i2 = ft_strlen(s2) - 1;
	while (i1 > 0 && (s1[i1] == ' ' || s1[i1] == '\n' || s1[i1] == '\t'))
		i1--;
	if (n == 0)
		return (0);
	while (i1 >= 0 && i2 >= 0 && n)
	{
		if (s1[i1] != s2[i2])
			break ;
		i1--;
		i2--;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char) s1[i1] - (unsigned char) s2[i2]);
}

// fonction de test seulement c'est pour ca je laisse mes for
// void	print_map(char **map, int rows, int cols)
// {
// 	for (int y = 0; y < rows; y++)
// 	{
// 		for (int x = 0; x < cols; x++)
// 			printf("%c", map[y][x]);
// 		printf("\n");
// 	}
// }

void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}
