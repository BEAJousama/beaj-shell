# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imabid <imabid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 12:34:40 by obeaj             #+#    #+#              #
#    Updated: 2022/04/28 14:43:31 by imabid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =  minishell.c \
		pwd.c \
		executor.c \
		echo.c \
		cd.c \
		export.c \
		env.c \
		unset.c \
		glob_utils_2.c \
		glob_utils.c \
		glob_utils_1.c \
		expander_utils.c \
		export_utils.c \
		exit.c \
		

SRCS_B = 

OBJS  = ${addprefix src/,${SRCS:.c=.o}}

OBJS_B  = ${addprefix src/bonus/,${SRCS_B:.c=.o}}

LD_FLAGS = -lft -L libft -lreadline

HEAD  = -I includes -I libft

CC = cc

CFLAGS = -Wall -Werror -Wextra

.c.o :
	${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME) : ${OBJS}
	make -C libft
	${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o $@

all : ${NAME}

bonus : ${OBJS_B}
	make -C libft
	${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS_B} -o ${NAME} 

clean :
	make clean -C libft
	@rm -rf ${OBJS} ${OBJS_B}

fclean : clean
	make fclean -C libft
	@rm -rf ${NAME}

re : fclean all