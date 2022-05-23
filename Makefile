NAME	= cub3d
LIBFT	= libft.a

SRCS	= sources/main.c sources/utils/getline.c
OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -rf

UNAME_S	:= $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LFLAGS = -L ./mlx -lmlx_Linux -lXext -lX11 -lm -lz -L. -lft
endif
ifeq ($(UNAME_S), Darwin)
	LFLAGS	= -lmlx -framework OpenGL -framework AppKit -L. -lft
endif
CFLAGS	= -Werror -Wall -Wextra -g -O3 -ffast-math -funsafe-math-optimizations

$(LIBFT):
		#@git clone 
		@${MAKE} -C libft/
		@cp libft/libft.a .
		@cp libft/libft.h includes/
		#@${RM} libft/

%.o:%.c
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@echo "Making Cub3D."
			@${CC} -g ${OBJS} -o ${NAME} ${LFLAGS}
			@echo "Done."

clean:
		@echo "Cleaning objects."
		@${RM} ${OBJS}
		@echo "Done."

fclean:		clean	
		@echo "Cleaning libft."
		@${MAKE} -C libft fclean
		@${RM} libft.a
		@${RM} includes/libft.h
		@echo "Cleaning binary."
		@${RM} ${NAME}
		@echo "Done."

re:			fclean all

.PHONY:		all clean fclean re
