# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:17:00 by franmart          #+#    #+#              #
#    Updated: 2023/06/07 11:01:03 by franmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

CC			= gcc
FLAGS 		= -Wall -Wextra -Werror
RM			= rm -rf

ifdef DEBUG
	FLAGS += -g
endif

SRC_DIR 	= src/

OBJ_DIR		= obj/

_SRC 		=	builtins/builtins_utils.c\
				builtins/builtins.c\
				builtins/cd.c\
				builtins/check_exit.c\
				builtins/enviroment_utils.c\
				builtins/enviroment.c\
				builtins/error.c\
				builtins/export.c\
				builtins/here_doc.c\
				executor/exec_utils.c\
				executor/exec.c\
				expander/expander_utils.c\
				expander/expander.c\
				expander/wildcard_expander.c\
				parser/cmdlst.c\
				parser/envlst_utils.c\
				parser/envlst.c\
				parser/fill_cmds.c\
				parser/lexer_utils.c\
				parser/lexer.c\
				parser/quotes.c\
				parser/tokens_utils.c\
				parser/tokens.c\
				prompt/prompt.c\
				signals/signals.c\
				utils/array_utils.c\
				utils/ato_int128.c\
				wildcard/wildcard.c\
				main.c

SRC 		= ${addprefix ${SRC_DIR}, ${_SRC}}
OBJ			= ${patsubst ${SRC_DIR}%.c, ${OBJ_DIR}%.o, ${SRC}}

LIBS		= ${LIBFT_DIR}/libft.a -lreadline

LIBFT_DIR	= libft

INCLUDES	= -I ./include -I ./${LIBFT_DIR}/include

SYS	= $(shell uname -s)

ifeq ($(SYS), Darwin)
	INCLUDES +=	-I /opt/vagrant/embedded/include
	LIBS	+= -L/opt/vagrant/embedded/lib
endif

${NAME}:	 ${OBJ}
			@echo "Compiling $(NAME)..."
			@echo "Compiling dependencies..."
			@$(MAKE) -s all -C $(LIBFT_DIR)
			@$(CC) ${FLAGS} $(INCLUDES) $(OBJ) -o $(NAME) $(LIBS)
			@echo "$(NAME) compiled!"

${OBJ_DIR}%.o: ${SRC_DIR}%.c
			@git submodule update --init
			@mkdir -p ${OBJ_DIR}/parser ${OBJ_DIR}/signals ${OBJ_DIR}/expander\
				 ${OBJ_DIR}/executor ${OBJ_DIR}/builtins ${OBJ_DIR}/prompt\
				 ${OBJ_DIR}/utils ${OBJ_DIR}/wildcard
			@${CC} ${FLAGS} ${INCLUDES} -c $^ -o $@ -g3

all:		${NAME} ${LIBFT}

clean:
			@echo "Removing files..."
			@echo "Removing dependencies..."
			@$(MAKE) -s clean -C $(LIBFT_DIR)
			@${RM} ${OBJ}

fclean: 	clean
			@${RM} ${NAME}
			@$(MAKE) -s fclean -C  $(LIBFT_DIR)

re:		fclean all

.PHONY:	all clean fclean re bonus
