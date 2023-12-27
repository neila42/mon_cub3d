/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/12/27 17:33:49 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*fill_with_space(char *line, t_data *data)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(line);
	while (len < (size_t)data->x_lenm)
	{
		tmp = line;
		line = ft_strjoin(line, " ");
		if (!line)
			fail("Error strjoin set_space");
		free(tmp);
		len++;
	}
	return (line);
}

int	fill_map(char *in_file, t_data *data)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		y;

	y = 0;
	fd = open(in_file, O_RDONLY);
	if (fd < 0)
		fail("fail open (fill_map)");
	data->map = malloc(data->y_lenm * sizeof(char *));
	if (!data->map)
		fail("malloc error (fill_map)");
	line = ignore_texture(fd);
	if (!line)
	{
		free(line);
		fail("No map found");
	}
	while (y < data->y_lenm && line != NULL)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		if (!line)
			fail("Error strtrim (fill_map)");
		if (ft_strlen(line) < (size_t)data->x_lenm)
		{
			line = fill_with_space(line, data);
		}
		free(tmp);
		data->map[y] = line;
		y++;
		if (y < data->y_lenm)
			line = get_next_line(fd);
	}
	close(fd);
	if (y != data->y_lenm)
		fail("Map size does not match expected dimensions");
	return (0);
}

int	check_auth_char(char *line, t_data *data)
{
	char	*ptr;
	int		len;

	ptr = line;
	while (line && *ptr)
	{
		if (!(*ptr == '0' || *ptr == '1' || *ptr == 'N' || *ptr == 'S' ||
				*ptr == 'W' || *ptr == 'E' || *ptr == ' ' || *ptr == '\t'))
		{
			printf("ERROR : %c\n", *ptr);
			return (1);
		}
		ptr++;
	}
	len = ft_strlen(line);
	if (len > data->x_lenm)
		data->x_lenm = len;
	return (0);
}

int	len_map(char *file_d, t_data *data)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(file_d, O_RDONLY);
	if (fd < 0)
		fail("can't open file");
	line = ignore_texture(fd);
	free(line);
	data->y_lenm = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
		if (check_auth_char(line, data))
		{
			free(line);
			close(fd);
			fail("char bizarre found");
		}
		free(line);
		data->y_lenm++;
	}
	close(fd);
	return (0);
}

//fonction final
int	parse_map(char *file_d, t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	if (reverse_strncmp(file_d, ".cub", 4) != 0)
		fail("map not a .cub file");
	fd = open(file_d, O_RDONLY);
	if (fd == -1)
		fail("cannot open .cub file");
	len_map(file_d, data);
	if (parse_textures(file_d, data) != 0)
		fail("error parse_textures");
	convert_colors(data);
	free(data->colors.f_color);
	free(data->colors.c_color);
	data->map = malloc(data->y_lenm * sizeof(char *));
	while (i < data->y_lenm)
	{
		data->map[i] = calloc(data->x_lenm, sizeof(char));
		i++;
	}
	if (!data->map)
		fail("Error when allocating map memory");
	i = 0;
	while (i < data->y_lenm)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	if (fill_map(file_d, data) != 0)
		fail("Error filling the map");
	// print_map(data->map, data->y_lenm, data->x_lenm); // a enlever apres
	if (check_walls(data) != 0)
		fail("Error not enough walls in map");
	if (data->player_x == 0 || data->player_y == 0)
		fail("No start position found");
	close(fd);
	return (0);
}

//main de test pour verifier que mes fonctions ont un bon comportement / debug
// int	main(int argc, char **argv) 
// {
// 	t_data	data;

// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
// 		return (1);
// 	}
// 	if (parse_map(argv[1], &data) != 0)
// 	{
// 		perror("Failed to parse the map\n");
// 		return (1);
// 	}
// 	printf("Map parsing successful!\n");
// 	printf("Player Start Position: (%d, %d)\n", data.player_x, data.player_y);
// 	printf("Map Dimensions: %d x %d\n", data.x_lenm, data.y_lenm);
// 	for (int i = 0; i < data.y_lenm; i++) {
// 		free(data.map[i]);
// 	}
// 	free(data.map);
// 	return (0);
// }
