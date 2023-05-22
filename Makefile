NAME 		= minishell

CC			= gcc
FLAGS 		= -Wall -Wextra -Werror
RM			= rm -rf

ifdef DEBUG
	FLAGS += -g
endif

SRC_DIR 	= src/

OBJ_DIR		= obj/

_SRC 		= parser/lexer.c 	\
			parser/lexer_utils.c\
			parser/tokens.c		\
			parser/tokens_utils.c\
			parser/fill_cmds.c	\
			parser/quotes.c		\
			expander/expander.c	\
			expander/expander_utils.c	\
			expander/wildcard_expander.c	\
			signals/signals.c	\
			cmdlst.c			\
			enviroment.c		\
			enviroment_utils.c	\
			builtins.c			\
			builtins_utils.c	\
			array_utils.c		\
			exec.c				\
			exec_utils.c		\
			envlst.c			\
			envlst_utils.c		\
			export.c			\
			cd.c				\
			pruebas.c			\
			here_doc.c			\
			wildcard.c			\
			error.c				\
			prompt.c			\
			ato_int128.c		\
			check_exit.c		\
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
			@$(CC) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBS)
			@echo "$(NAME) compiled!"

${OBJ_DIR}%.o: ${SRC_DIR}%.c
			@git submodule update --init
			@mkdir -p ${OBJ_DIR}/parser ${OBJ_DIR}/signals ${OBJ_DIR}/expander
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
