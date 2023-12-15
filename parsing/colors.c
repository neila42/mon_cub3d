#include "parse.h"

int	get_rgb(int dir, char *line, t_data *data)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (tmp == NULL)
		fail("In get_color");
	if (dir == FLOOR)
	{
		data->colors.f_color = ft_strdup(tmp[1]);
		if (data->colors.f_color == NULL)
			fail("In get_color");
		data->colors.f_color[ft_strlen(tmp[1]) - 1] = 0;
	}
	else if (dir == CEILING)
	{
		data->colors.c_color = ft_strdup(tmp[1]);
		if (data->colors.c_color == NULL)
			fail("In get_color");
		data->colors.c_color[ft_strlen(tmp[1]) - 1] = 0;
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (0);
}

int	convert_color(char **c)
{
	int	tmp;

	tmp = (ft_atoi(c[0]) << 16) | (ft_atoi(c[1]) << 8) | ft_atoi(c[2]);
	free(c[0]);
	free(c[1]);
	free(c[2]);
	free(c);
	return (tmp);
}

int	check_value(char *rgb_str, unsigned int i)
{
	unsigned int	j;
	char			*tmp_str;
	int				tmp;

	j = i;
	while (ft_isdigit(rgb_str[i]))
		i++;
	if (i - j == 0 || i - j > 3)
		fail("No number or Number too big.");
	tmp_str = ft_substr(rgb_str, j, 3);
	if (!tmp_str)
		fail("Error allocating memory.");
	tmp = ft_atoi(tmp_str);
	free(tmp_str);
	if (tmp < 0 || tmp > 255)
		return (-1);
	return ((int) i);
}

int	check_format(char *rgb_str)
{
	int	i;

	i = 0;
	if (!rgb_str)
		fail("No color found.");
	i = check_value(rgb_str, (unsigned int) i);
	if (i < 0 || rgb_str[i++] != ',')
		return (1);
	i = check_value(rgb_str, (unsigned int) i);
	if (i < 0 || rgb_str[i++] != ',')
		return (1);
	i = check_value(rgb_str, (unsigned int) i);
	if (i < 0)
		return (1);
	return (0);
}

int	convert_colors(t_data *data)
{
	char	**tmp;

	if (check_format(data->colors.c_color))
		fail("Wrong format for ceiling color.");
	if (check_format(data->colors.f_color))
		fail("Wrong format for floor color.");
	tmp = ft_split(data->colors.f_color, ',');
	if (tmp == NULL)
		fail("In convert_colors");
	data->colors.floor = convert_color(tmp);
	tmp = ft_split(data->colors.c_color, ',');
	if (tmp == NULL)
		fail("In convert_colors");
	data->colors.ceiling = convert_color(tmp);
	return (0);
}
