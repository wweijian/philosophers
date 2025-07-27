# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weijian <weijian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/26 14:37:42 by weijian           #+#    #+#              #
#    Updated: 2025/07/27 23:25:13 by weijian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -O0 -Iphilo/

PHILO_DIR =
PHILO = main.c \
		convert.c init_philo.c \
		philo.c actions.c \
		utils.c exit.c

# PHILO := $(addprefix ${PHILO_DIR}, ${PHILO})

all: ${NAME}

${NAME}: ${PHILO}
	${CC} ${CFLAGS} ${PHILO} -o ${NAME}

clean:
	rm ${NAME}