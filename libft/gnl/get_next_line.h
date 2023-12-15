/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:11:03 by nmuminov          #+#    #+#             */
/*   Updated: 2023/12/14 16:09:31 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_line(char *stash);
int		ft_find_new_line(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_free(char *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
