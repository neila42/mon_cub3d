/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/12/27 17:33:28 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <unistd.h>
# include "../libft/gnl/get_next_line.h"
# include <string.h>
# include <sys/errno.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef enum e_orientation {
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR,
}	t_orientation;

typedef enum e_fc {
	CEILING,
	FLOOR,
}	t_fc;

typedef struct s_color_info {
	char	*f_color;
	char	*c_color;
	int		floor;
	int		ceiling;
}	t_color_info;

typedef struct s_data {
	int				player_orientation;
	int				player_x;
	int				player_y;
	int				x_lenm;
	int				y_lenm;
	char			**map;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*door_path;
	t_color_info	colors;
}	t_data;

// pour pouvoir utiliser les touches du clavier pour se deplacer
// typedef enum e_key { 
// 	KEY_A = 0,
// 	KEY_S = 1,
// 	KEY_D = 2,
// 	KEY_W = 13,
// 	KEY_DESTROY = 17,
// 	KEY_ESCAPE = 53,
// }	t_key;

//func
int		reverse_strncmp(const char *s1, const char *s2, size_t n);
void	fail(char *str);
int		get_texture_path(t_orientation dir, char *line, t_data *data);
int		get_path_texture(char *path, char **texture_path, char *error_message);
int		parse_textures(char *file_d, t_data *data);
int		is_space_udlr(int x, int y, t_data *data);
int		is_space_udr(int x, int y, t_data *data);
int		is_space_udl(int x, int y, t_data *data);
int		check_space(int x, int y, t_data *data);
int		check_first_last(t_data *data);
char	*ignore_texture(int fd_cub);
int		player_pos(int x, int y, t_data *data);
int		check_auth_char(char *line, t_data *data);
int		len_map(char *file_d, t_data *data);
int		check_walls(t_data *data);
char	*fill_with_space(char *line, t_data *data);
int		fill_map(char *file_d, t_data *data);
int		get_rgb(int dir, char *line, t_data *data);
int		convert_color(char **c);
int		convert_colors(t_data *data);
int		check_format(char *rgb_str);
int		check_value(char *rgb_str, unsigned int i);
// void	print_map(char **map, int rows, int cols);
int		cross_check(t_data *data);

#endif
