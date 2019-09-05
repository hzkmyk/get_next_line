/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyake <hmiyake@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 20:09:27 by hmiyake           #+#    #+#             */
/*   Updated: 2019/09/05 12:28:58 by hmiyake          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		new_line_checker(int fd, char **line, char **str)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	if (str[fd][i] == '\n')
	{
		*line = ft_strsub(str[fd], 0, i);
		temp = ft_strdup(str[fd] + i + 1);
		ft_strdel(&str[fd]);
		if (*temp)
			str[fd] = ft_strdup(temp);
		ft_strdel(&temp);
	}
	else
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

void	temp_to_str(int fd, char **str, char *buff)
{
	char *temp;

	temp = ft_strjoin(str[fd], buff);
	ft_strdel(&str[fd]);
	str[fd] = ft_strdup(temp);
	ft_strdel(&temp);
}

int		get_next_line(const int fd, char **line)
{
	int			readsize;
	static char	*str[1024];
	char		buff[BUFF_SIZE + 1];

	if (!line || fd < 0)
		return (-1);
	*line = NULL;
	while ((readsize = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (str[fd] == NULL)
			str[fd] = ft_strnew(0);
		buff[readsize] = '\0';
		temp_to_str(fd, str, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (readsize < 0)
		return (-1);
	if (readsize == 0 && str[fd] == NULL)
	{
		if (*line)
			ft_strdel(line);
		return (0);
	}
	return (new_line_checker(fd, line, str));
}
