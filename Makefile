NAME		= cub3d
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-fsanitize=address #O3 #-g3 
RM			= rm -rf

OBJ			= $(SRC:.c=.o)

SRC =	parsing/util_parse.c \
		parsing/parse.c \
		parsing/colors.c \
		parsing/path.c \
		parsing/walls.c \

all:	$(NAME)

%.o : %.c
	${CC} -c -o $@ $^ -I ./libft ${CFLAGS}
	
$(NAME):	$(OBJ) 
			${MAKE} -C libft 
			$(CC) ${CFLAGS} -o ${NAME} ${OBJ} -framework OpenGL -framework AppKit -L./libft -lft

libft:
			${MAKE} -C libft

clean:
			$(RM) $(OBJ)
			$(MAKE) -C libft clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C libft fclean

re:			fclean all

.PHONY:		all libft clean fclean re
