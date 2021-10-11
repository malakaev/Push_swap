# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 21:15:13 by kgolda            #+#    #+#              #
#    Updated: 2021/10/11 21:15:29 by kgolda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_BONUS = checker

SRCS = push_swap.c\
		ft_exit.c\
		conv_check.c\
		make_stack.c\
		pa_pb_sa.c\
		ra_rra_rb_rrb.c\
		rr_rrr.c\
		scoring.c\
		sort.c

SRCS_BONUS = checker.c\
		ft_exit.c\
		conv_check.c\
		make_stack.c\
		bonus_sa_sb_ss.c\
		bonus_pa_pb.c\
		ra_rra_rb_rrb.c\
		rr_rrr.c\
		scoring.c\
		bonus_utils.c\
		ft_strlen.c\
		get_next_line.c\
		ft_strncmp.c

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

HEADER = push_swap.h

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

RM = rm -f

${NAME}: ${OBJS} $(HEADER)
	$(CC) ${OBJS} -o ${NAME}

${NAME_BONUS}: ${SRCS_BONUS} ${OBJS_BONUS} $(HEADER)
	$(CC) ${OBJS_BONUS} -o ${NAME_BONUS}

%.o: %.c
	$(CC) $(CFLAGS) $< -c

all: ${NAME} ${NAME_BONUS}

bonus: ${NAME_BONUS}

clean:
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	${RM} ${NAME} ${NAME_BONUS}

re: fclean all

.PHONY: all clean fclean re
