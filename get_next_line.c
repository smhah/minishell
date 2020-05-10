/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:01:36 by smhah             #+#    #+#             */
/*   Updated: 2019/10/30 20:09:18 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char    *ft_strdup(char *str)
{
        size_t   leng;
        unsigned int    i;
        char                    *dup;

        i = 0;
        leng = ft_strlen((char *)str);
        dup = (char *)malloc((sizeof(char) * (leng + 1)));
        if (dup == 0)
                return (0);
        while (str[i] != '\0')
        {
                dup[i] = str[i];
                i++;
        }
        dup[i] = str[i];
        return (dup);
}

 int    ft_boucle(char **p, char **buffer,char **line, int fd)
 {
        char *pp;
        int j;

        while(1)
        {
                if(!(*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
                       return (-1);
                j = read(fd, *buffer, BUFFER_SIZE);
                if (*buffer[0] == '\0' || j == 0)
                {
                        pp = *p;
                        line[0] = ft_strdup(*p);
                        free(pp);
                        *p = ft_strdup("");
                        free(*buffer);
                        break;
                }
                *(*buffer + j) = '\0';
                if (strchr(*buffer,'\n'))
                        return(1) ;
                pp = *p;
                *buffer = ft_strjoin(*p, *buffer);
                free(pp);
                *p = ft_strdup(*buffer);
                free(*buffer);
        } 
        return(0);
 }
 
int get_next_line(int fd, char **line)
{
        static char *p;
        char *buffer;
        int j;
        char *pp;

        buffer = NULL;
        if(!p)
                p = ft_strdup("");
        if(strchr(p,'\n') == 0)
                if ((j = ft_boucle(&p, &buffer, line, fd)) <= 0)
                        return (j);
        j = 0;
        pp = p;
        if (!buffer)
                buffer = ft_strjoin(p, "");
        else   
           buffer = ft_strjoin(p, buffer);
        free(pp);
        while (strchr("\n\0", buffer[j]) == 0)
                j++;
        p = ft_substr(buffer, j + 1, ft_strlen(buffer) - j + 1);
        line[0] = ft_substr(buffer,0,j);
        free(buffer);
        return (1);
}