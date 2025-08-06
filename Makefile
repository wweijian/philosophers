# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weijian <weijian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/26 14:37:42 by weijian           #+#    #+#              #
#    Updated: 2025/08/06 16:07:49 by weijian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -O0 -Iphilo/

SRCS_DIR = philo/
SRCS = main.c \
		init_data.c init_philo.c \
		philo.c actions.c \
		utils.c exit.c
SRCS := $(addprefix ${SRCS_DIR}, ${SRCS})
NAME := $(addprefix ${SRCS_DIR}, ${NAME})

OBJS_DIR = philo/objs/
OBJS := $(addprefix ${OBJS_DIR}, $(notdir ${SRCS:.c=.o}))

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo done

${OBJS}: ${OBJS_DIR}%.o: ${SRCS_DIR}%.c | ${OBJS_DIR}
	${CC} ${CFLAGS} -c $< -o $@
	
${OBJS_DIR}:
	mkdir ${OBJS_DIR}

clean:
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re