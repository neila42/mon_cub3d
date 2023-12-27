/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/12/27 17:32:42 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_texture_path(t_orientation dir, char *line, t_data *data)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (!tmp)
		fail("split error");
	if (reverse_strncmp(tmp[1], ".xpm", 4) != 0)
		fail("Texture not a xpm file");
	if (dir == NORTH)
		get_path_texture(tmp[1], &data->no_path, "fail to open North texture");
	else if (dir == SOUTH)
		get_path_texture(tmp[1], &data->so_path, "fail to open South texture");
	else if (dir == WEST)
		get_path_texture(tmp[1], &data->we_path, "fail to open West texture");
	else if (dir == EAST)
		get_path_texture(tmp[1], &data->ea_path, "fail to open East texture");
	else if (dir == DOOR)
		get_path_texture(tmp[1], &data->door_path, "fail to open Door texture");
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (0);
}

//com perso : free dans le if?
int	get_path_texture(char *path, char **texture_path, char *error_message)
{
	*texture_path = ft_strdup(path);
	if (!(*texture_path))
		fail("memory error get_path_texture");
	(*texture_path)[ft_strlen(*texture_path) - 1] = 0;
	if (open(*texture_path, O_RDONLY) < 0)
		fail(error_message);
	free(*texture_path);
	return (0);
}

int	parse_textures(char *file_d, t_data *data)
{
	int		fd;
	int		line_counter;
	char	*line;
	char	*trimmed_line;

	line_counter = 0;
	fd = open(file_d, O_RDONLY);
	if (fd < 0)
		fail("Error opening file (parse_texture)");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trimmed_line = line;
		while (*trimmed_line == ' ' || *trimmed_line == '\t')
			trimmed_line++;
		if (!ft_strncmp(trimmed_line, "NO", 2))
		{
			get_texture_path(NORTH, trimmed_line, data);
			line_counter++;
		}
		else if (!ft_strncmp(trimmed_line, "SO", 2))
		{
			get_texture_path(SOUTH, trimmed_line, data);
			line_counter++;
		}
		else if (!ft_strncmp(trimmed_line, "WE", 2))
		{
			get_texture_path(WEST, trimmed_line, data);
			line_counter++;
		}
		else if (!ft_strncmp(trimmed_line, "EA", 2))
		{
			get_texture_path(EAST, trimmed_line, data);
			line_counter++;
		}
		else if (!ft_strncmp(trimmed_line, "F", 1))
		{
			get_rgb(FLOOR, trimmed_line, data);
			line_counter++;
		}
		else if (!ft_strncmp(trimmed_line, "C", 1))
		{
			get_rgb(CEILING, trimmed_line, data);
			line_counter++;
		}
		free(line);
	}
	close(fd);
	if (line_counter != 6)
		fail("Incorrect number of texture/color lines");
	return (0);
}

char	*ignore_texture(int fd_cub)
{
	char	*line;
	char	*ptr;

	while (1)
	{
		line = get_next_line(fd_cub);
		if (!line)
			fail("error line ignoretexture");
		ptr = line;
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (ft_strncmp(ptr, "NO ", 3) == 0 || ft_strncmp(ptr, "SO ", 3) == 0
			||ft_strncmp(ptr, "WE ", 3) == 0 || ft_strncmp(ptr, "EA ", 3) == 0
			||ft_strncmp(ptr, "F ", 2) == 0 || ft_strncmp(ptr, "C ", 2) == 0)
		{
			free(line);
			continue ;
		}
		if (!(*ptr == '0' || *ptr == '1' || *ptr == 'N' || *ptr == 'S' ||
				*ptr == 'W' || *ptr == 'E'))
		{
			free(line);
			continue ;
		}
		return (line);
	}
}
