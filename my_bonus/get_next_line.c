/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:45:01 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/11 20:45:05 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ft_if_read_null(char *ex_buf, size_t *ex_size)
{
	char	*buf_new;

	if (*ex_size == 0)
	{
		buf_new = (char *)malloc(sizeof(char));
		if (buf_new == 0)
			return (0);
		buf_new[0] = '\0';
		return (buf_new);
	}
	*ex_size = 0;
	return (ex_buf);
}

t_buf_ind	ft_read_to_buf(char **line, int fd, t_buf_ind bfi, char **buf)
{
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	if (*buf == 0)
	{
		bfi.err = -1;
		return (bfi);
	}
	bfi.r = read(fd, *buf, BUFFER_SIZE);
	bfi.err = 1;
	if (bfi.r == -1lu)
	{
		free(*buf);
		bfi.err = -1;
	}
	if (bfi.r == 0)
	{
		*line = mem_join(*line, bfi, buf);
		free(*buf);
		*buf = 0;
		bfi.err = 0;
		if (*line == 0)
			bfi.err = -1;
	}
	return (bfi);
}

t_buf_ind	ft_eof_freebuf(t_buf_ind bfi, char **buf, char **line, char *temp)
{
	*line = mem_join(temp, bfi, buf);
	if (temp != 0)
		free(temp);
	if (*line == 0)
	{
		bfi.flag = -1;
		free(*buf);
		return (bfi);
	}
	if ((*buf)[bfi.i] == '\n')
	{
		if (bfi.i == (bfi.r - 1))
		{
			bfi.i = 0;
			free(*buf);
			*buf = 0;
		}
		bfi.flag = 1;
		return (bfi);
	}
	bfi.i = 0;
	free(*buf);
	*buf = 0;
	bfi.flag = 0;
	return (bfi);
}

char	*mem_join(char *ex_buf, t_buf_ind bfi, char **buf)
{
	char			*buf_new;
	static size_t	ex_size;
	size_t			j;

	buf_new = 0;
	if (bfi.r == 0)
		return (ft_if_read_null(ex_buf, &ex_size));
	buf_new = (char *)malloc(sizeof(char) * (ex_size + bfi.i + 2 - bfi.ex_i));
	if (buf_new == 0)
		return (0);
	j = -1;
	while (++j < ex_size)
		buf_new[j] = ex_buf[j];
	ex_size = ex_size + bfi.i + 1 - bfi.ex_i;
	while (j < ex_size)
		buf_new[j++] = (*buf)[bfi.ex_i++];
	if ((*buf)[bfi.i] == '\n')
	{
		buf_new[j - 1] = '\0';
		ex_size = 0;
	}
	else
		buf_new[j] = '\0';
	return (buf_new);
}

int	get_next_line(int fd, char **line)
{
	static char			*buf;
	static t_buf_ind	bfi;

	if (line != NULL)
	{
		*line = 0;
		while ((fd >= 0) && (BUFFER_SIZE > 0) && ((read(fd, NULL, 0)) != -1))
		{
			if (buf == 0)
			{
				bfi = ft_read_to_buf(line, fd, bfi, &buf);
				if (bfi.err == 0 || bfi.err == -1)
					return (bfi.err);
			}
			else
				bfi.i = bfi.i + 1;
			bfi.ex_i = bfi.i;
			while ((bfi.i < (bfi.r - 1)) && (buf[bfi.i] != '\n'))
				bfi.i++;
			bfi = ft_eof_freebuf(bfi, &buf, line, *line);
			if (bfi.flag == 1 || bfi.flag == -1)
				return (bfi.flag);
		}
	}
	return (-1);
}
