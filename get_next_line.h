/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:53:56 by smhah             #+#    #+#             */
/*   Updated: 2019/10/30 18:55:12 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1028
int		get_next_line(int fd, char **line);
size_t  ft_strlen(const char *str);
char    *ft_strchr(const char *str, int c);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strdup(char *str);
#endif
