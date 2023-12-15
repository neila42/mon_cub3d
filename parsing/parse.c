#include "parse.h"

int	check_first_last(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->x_lenm) //en haut
	{
		if (data->map[0][x] == '0')
			return (1);
		x++;
	}
	x = 0;
	while (x < data->x_lenm) //en bas 
	{
		if (data->map[data->y_lenm - 1][x] == '0')
			return (1);
		x++;
	}
	return (0);
}

int	player_pos(int x, int y, t_data *data)
{
	if (data->player_x != 0 || data->player_y != 0)
		fail("Multiple start position found on map.");
	data->player_x = x;
	data->player_y = y;
	data->player_orientation = data->map[x][y];
	data->map[x][y] = '0'; //espace navigable
	return (0);
}

//check 4 directions
int	is_space_udlr(int x, int y, t_data *data)
{
	return (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
			|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ');
}

int	is_space_udr(int x, int y, t_data *data)
{
	return (data->map[y][x] == ' '
		|| (y + 1 < data->y_lenm && data->map[y + 1][x] == ' ')
		|| (x + 1 < data->x_lenm && data->map[y][x + 1] == ' '));
}

int	is_space_udl(int x, int y, t_data *data)
{
	return (data->map[y][x + 1] == ' ' || data->map[y][x - 1] == ' '
		|| (y > 0 && data->map[y - 1][x] == ' ')
		|| (y < data->y_lenm - 1 && data->map[y + 1][x] == ' '));
}

// bord entouré de mur (inverse = espace)
int	check_space(int x, int y, t_data *data)
{
	if (x == 0)
	{
		if (is_space_udr(x, y, data))
			fail("not enough walls (udr)");
	}
	else if (x == data->x_lenm - 1)
	{
		if (is_space_udl(x, y, data))
			fail("not enough walls (udl)");
	}
	else
	{
		if (is_space_udlr(x, y, data))
			fail("not enough walls (udlr)");
	}
	return (0);
}

int	check_walls(t_data *data)
{
	int x;
	int y;
	char i_char;

	data->player_x = 0;
	data->player_y = 0;
	data->player_orientation = NORTH; //init du joueur tout ici
	if (check_first_last(data))
		fail("not enough walls");
	y = 1;
	while (y < data->y_lenm - 1)
	{
		x = 0;
		while (x < data->x_lenm)
		{
			i_char = data->map[y][x];
			if (i_char == '0')
				check_space(x, y, data);
			if (i_char == 'N' || i_char == 'S' || i_char == 'W'
				|| i_char == 'E')
				player_pos(x, y, data);
			x++;
		}
		y++;
	}
	return (0);
}

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

int fill_map(char *in_file, t_data *data) {
    int fd;
    char *line;
    char *tmp;
    int y = 0;

    fd = open(in_file, O_RDONLY);
    if (fd < 0)
        fail("Error opening file");

    data->map = malloc(data->y_lenm * sizeof(char *));
    if (!data->map)
        fail("Error allocating memory for map");
    line = ignore_texture(fd);
    if (!line)
        fail("No map found in file");

    do {
        tmp = line;
        line = ft_strtrim(line, "\n");
        if (!line)
            fail("Error in ft_strtrim");

        if (ft_strlen(line) < (size_t)data->x_lenm)
            line = fill_with_space(line, data);

        data->map[y] = line;
        y++;
        free(tmp);

        if (y < data->y_lenm)
            line = get_next_line(fd);
    } while (y < data->y_lenm && line != NULL);
    close(fd);
    if (y != data->y_lenm)
        fail("Map size does not match expected dimensions");
    return(0);
}

int	check_auth_char(char *line, t_data *data)
{
	char	*ptr;
	int		len;

	ptr = line;
	while (line && *ptr)
	{
		if (!(*ptr == '0' || *ptr == '1' || *ptr == 'N' || *ptr == 'S' ||
				*ptr == 'W' || *ptr == 'E' || *ptr == ' '))
			return (1);
		ptr++;
	}
	len = ft_strlen(line);
	if (len > data->x_lenm)
		data->x_lenm = len; //x len
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
	data->y_lenm = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
		if (check_auth_char(line, data)) // +update de x_len
		{
			close(fd);
			free(line);
			fail("char bizarre found");
		}
		free(line);
		data->y_lenm++; // y len 
	}
	data->y_lenm ++;
	close(fd);
	return (0);
}
// fonction de test seulement c'est pour ca je laisse mes for
void	print_map(char **map, int rows, int cols) 
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
			printf("%c", map[y][x]);
		printf("\n");
	}
}

//fonction final
int parse_map(char *file_d, t_data *data)
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
	if (fill_map(file_d, data) != 0)
		fail("Error filling the map");
	printf("%d\n %d\n", data->x_lenm, data->y_lenm);
	print_map(data->map, data->y_lenm, data->x_lenm); // a enlever apres
	check_walls(data);
	if (data->player_x == 0 || data->player_y == 0)
		fail("No start position found");
	close(fd);
	return (0);
}

//main de test pour verifier que mes fonctions ont un bon comportement / debug
int	main(int argc, char **argv) 
{
	t_data	data;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (parse_map(argv[1], &data) != 0)
	{
		perror("Failed to parse the map\n");
		return (1);
	}
	printf("Map parsing successful!\n");
	printf("Player Start Position: (%d, %d)\n", data.player_x, data.player_y);
	printf("Map Dimensions: %d x %d\n", data.x_lenm, data.y_lenm);
	return (0);
}
