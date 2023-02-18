NAME 		= minishell

CC			= gcc
FLAGS 		= -Wall -Wextra -Werror
RM			= rm -rf

ifdef DEBUG
	FLAGS += -g
endif

SRC_DIR 	= src/
_SRC 		= parser/lexer.c 	\
			parser/lexer_utils.c\
			parser/tokens.c		\
			parser/tokens_utils.c\
			ft_cmdlst.c			\
			enviroment.c		\
			enviroment_utils.c	\
			builtins.c			\
			builtins_utils.c	\
			array_utils.c		\
			exec.c				\
			exec_utils.c		\
			pruebas.c			\
			main.c

SRC 		= ${addprefix ${SRC_DIR}, ${_SRC}}
OBJ			= ${SRC:.c=.o}

LIBS		= lib/libft-juan-aga/libft.a -lreadline
LIBFT_DIR	= lib/libft-juan-aga

INCLUDES	= -I ./include -I ./${LIBFT_DIR}/include

${NAME}:	 ${OBJ}
			@echo "Compiling $(NAME)..."
			@echo "Compiling dependencies..."
			@git submodule update --init
			@$(MAKE) -s all -C $(LIBFT_DIR)
			@$(CC) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBS)
			@echo "$(NAME) compiled!"

%.o: %.c
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
