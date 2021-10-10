#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_buffer_index
{
	size_t	r;
	size_t	i;
	size_t	ex_i;
	int		flag;
	int		err;
}			t_buf_ind;

char		*ft_if_read_null(char *ex_buf, size_t *ex_size);
t_buf_ind	ft_read_to_buf(char **line, int fd, t_buf_ind bfi, char **buf);
t_buf_ind	ft_eof_freebuf(t_buf_ind bfi, char **buf, char **line, char *temp);
char		*mem_join(char *ex_buf, t_buf_ind bfi, char **buf);
int			get_next_line(int fd, char **line);

#endif
