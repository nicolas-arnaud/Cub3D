NAME	= cub3d
LIBFT	= libft.a

SRCS	= sources/main.c sources/parsing.c sources/getline.c sources/utils.c
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
CFLAGS	= -Werror -Wall -Wextra -O3 -ffast-math -funsafe-math-optimizations
	
%.o:%.c
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		$(NAME)

$(VERBOSE).SILENT:

$(LIBFT):
		${MAKE} -C libft/
		cp libft/libft.a .
		cp libft/libft.h includes/


$(NAME):	$(LIBFT) $(OBJS)
			echo Making Cub3D...
			${CC}  ${OBJS} -o ${NAME} ${LFLAGS}
			echo ✅

debug:		$(LIBFT)
			echo Making Cub3D with debug on...
			${CC} ${SRCS} -g -D DEBUG=1 ${CFLAGS} ${LFLAGS} -o ${NAME}
			echo ✅

clean:
		echo Cleaning objects...
		${RM} ${OBJS}
		echo ✅

fclean:		clean	
		${MAKE} -C libft fclean
		${RM} libft.a
		${RM} includes/libft.h
		echo Cleaning binary...
		${RM} ${NAME}
		echo ✅

re:			fclean all

.PHONY:		all clean fclean re debug
