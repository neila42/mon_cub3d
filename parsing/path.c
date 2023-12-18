/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/12/18 15:59:34 by Probook          ###   ########.fr       */
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

int	get_path_texture(char *path, char **texture_path, char *error_message)
{
	*texture_path = ft_strdup(path);
	if (!(*texture_path))
		fail("memory error get_path_texture");
	// printf("<%s>\n", *texture_path);
	// printf("%zu\n", ft_strlen(*texture_path));
	(*texture_path)[ft_strlen(*texture_path) - 1] = 0; //supp \n de fin
	if (open(*texture_path, O_RDONLY) < 0)
		fail(error_message);
	return (0);
}

int	parse_textures(char *file_d, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(file_d, O_RDONLY);
	if (fd < 0)
		fail("Error opening file (parse_texture)");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, "NO", 2))
			get_texture_path(NORTH, line, data);
		else if (!ft_strncmp(line, "SO", 2))
			get_texture_path(SOUTH, line, data);
		else if (!ft_strncmp(line, "EA", 2))
			get_texture_path(EAST, line, data);
		else if (!ft_strncmp(line, "WE", 2))
			get_texture_path(WEST, line, data);
		else if (!ft_strncmp(line, "D", 1))
			get_texture_path(DOOR, line, data);
		else if (!ft_strncmp(line, "C", 1))
			get_rgb(CEILING, line, data);
		else if (!ft_strncmp(line, "F", 1))
			get_rgb(FLOOR, line, data);
		free(line);
	}
	close(fd);
	return (0);
}

char *ignore_texture(int fd_cub)
{
    char *line;

    while (1)
    {
        line = get_next_line(fd_cub);
        if (!line)
            fail("error line ignoretexture");
        if (!(!ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2)
                || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
                || !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)
                || !ft_strncmp(line, "D", 1) || !ft_strncmp(line, "\n", 1)))
            break;
        free(line);
    }
    return (line);
}

