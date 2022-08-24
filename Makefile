NAME	=	cub3d
LIBFT	=	libft.a
MLX		=   includes/mlx.h


SRCS	=	src/main.c src/hooks.c src/vectors.c
SRCS	+=	src/parsing/parsing.c src/parsing/getline.c src/parsing/map.c src/parsing/utils.c
SRCS	+=	src/render/render.c src/render/minimap.c src/render/utils.c src/render/raycast.c
OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -rf

UNAME_S	:=	$(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LFLAGS	=	-L ./mlx -lmlx_Linux -lXext -lX11 -lm -lz -L. -lft
endif
ifeq ($(UNAME_S), Darwin)
	LFLAGS	= -L ./mlx -lmlx -framework OpenGL -framework AppKit -L. -lft
endif
CFLAGS	=	-Werror -Wall -Wextra -O3 -ffast-math -funsafe-math-optimizations
	
%.o:%.c
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		$(NAME)

$(VERBOSE).SILENT:

$(LIBFT):
		${MAKE} -C libft/
		cp libft/libft.a .
		cp libft/libft.h includes/

$(MLX):
		cp mlx/mlx.h includes/

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			echo Making Cub3D...
			${CC}  ${OBJS} ${LFLAGS} -o ${NAME} 
			echo ✅

debug:		$(LIBFT)
			echo Making Cub3D with debug on...
			${CC} ${SRCS} -g -fsanitize=address -D DEBUG=1 ${CFLAGS} ${LFLAGS} -o ${NAME}
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
