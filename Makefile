NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC_DIR = src/
_SRC = main.c

SRC = ${addprefix ${SRC_DIR}, ${_SRC}}
OBJ = ${SRC:.c=.o}

LIBFT = lib/libft-juan-aga/libft.a
LIBFT_DIR = lib/libft-juan-aga

INCLUDES = -Iinc -L ${LIBFT_DIR} -lft

${NAME}: ${OBJ}
	@echo "Compiling $(NAME)..."
	@echo "Compiling dependencies..."
	@$(MAKE) -s all -C $(LIBFT_DIR)
	@$(CC) $(INCLUDES) $(OBJ) -o $(NAME) $(INCLUDES)
	@echo "$(NAME) compiled!"

%.o: %.c
	@${CC} ${FLAGS} -c $^ -o $@ -g3

all: ${NAME} ${LIBFT}

clean:
	@echo "Removing files..."
	@echo "Removing dependencies..."
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}
	@$(MAKE) -s fclean -C  $(LIBFT_DIR)

re:	fclean all

.PHONY:	all clean fclean re bonus
