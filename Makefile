# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weijian <weijian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/26 14:37:42 by weijian           #+#    #+#              #
#    Updated: 2025/08/12 00:46:20 by weijian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- FILE NAME --- #

DIR = philo/

NAME = philo
NAME := $(addprefix ${DIR}, ${NAME})

# --- COMPILE RULES --- #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -pthread -O0

# --- DEFINTIONS --- #

SRCS_DIR = srcs/
SRCS = main.c philo.c actions.c
SRCS := $(addprefix ${SRCS_DIR}, ${SRCS})

INIT_DIR = init/
INIT = data.c philo.c mutex.c
INIT := $(addprefix ${INIT_DIR}, ${INIT})

UTIL_DIR = utils/
UTIL = mutex.c data.c cleanup.c
UTIL := $(addprefix ${UTIL_DIR}, ${UTIL})

SRCS += ${INIT} ${UTIL}
ALL_DIR = ${SRCS_DIR} ${INIT_DIR} ${UTIL_DIR}

INCL_DIR = ${DIR}includes/
INCL = philo.h
INCL := ${addprefix ${INCL_DIR}, ${INCL}}

# --- OBJECTS --- #

OBJS_DIR = ${DIR}objs/
OBJS_SUBDIR = $(addprefix ${OBJS_DIR}, ${ALL_DIR})
OBJS := $(addprefix ${OBJS_DIR}, ${SRCS:.c=.o})

# ---  RULES --- #

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo done

${OBJS}: ${OBJS_DIR}%.o: ${DIR}%.c | ${OBJS_SUBDIR}
	${CC} ${CFLAGS} -I${INCL_DIR} -c $< -o $@
	
${OBJS_SUBDIR}: %:
	mkdir -p $@

# --- CLEAN UP --- #

clean:
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

# --- PHONY --- #

.PHONY: all clean fclean re

.SILENT: ${OBJS} clean fclean ${OBJS_SUBDIR}