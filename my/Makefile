NAME = push_swap

SRCS = push_swap.c\
		ft_exit.c\
		conv_check.c\
		make_stack.c\
		pa_pb_sa.c\
		ra_rra_rb_rrb.c\
		rr_rrr.c\
		scoring.c\
		sort.c

OBJS = ${SRCS:.c=.o}

HEADER = push_swap.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

${NAME}: ${OBJS} $(HEADER)
	$(CC) ${OBJS} -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) $< $(HEADER) -c

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
