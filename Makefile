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
			parser/expander.c	\
			parser/fill_cmds.c	\
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
			main.c

SRC 		= ${addprefix ${SRC_DIR}, ${_SRC}}
OBJ			= ${patsubst ${SRC_DIR}%.c, ${OBJ_DIR}%.o, ${SRC}}

LIBS		= lib/libft-juan-aga/libft.a -lreadline memory-leaks/memory_leaks.a

LIBFT_DIR	= lib/libft-juan-aga

MEMORY_DIR	= memory-leaks

INCLUDES	= -I ./include -I ./${LIBFT_DIR}/include -I ./${MEMORY_DIR}/include

${NAME}:	 ${OBJ}
			@echo "Compiling $(NAME)..."
			@echo "Compiling dependencies..."
			@$(MAKE) -s all -C $(LIBFT_DIR)
			@${MAKE} -s all -C ${MEMORY_DIR}
			@$(CC) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBS)
			@echo "$(NAME) compiled!"

${OBJ_DIR}%.o: ${SRC_DIR}%.c
			@git submodule update --init
			@mkdir -p ${OBJ_DIR}/parser
			@${CC} ${FLAGS} ${INCLUDES} -c $^ -o $@ -g3

all:		${NAME} ${LIBFT}

clean:
			@echo "Removing files..."
			@echo "Removing dependencies..."
			@$(MAKE) -s clean -C $(LIBFT_DIR)
			@$(MAKE) -s clean -C $(MEMORY_DIR)
			@${RM} ${OBJ_DIR}

fclean: 	clean
			@${RM} ${NAME}
			@$(MAKE) -s fclean -C  $(LIBFT_DIR)
			@$(MAKE) -s fclean -C $(MEMORY_DIR)

re:		fclean all

.PHONY:	all clean fclean re bonus
