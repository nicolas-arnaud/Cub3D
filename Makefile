NAME	=	cub3d
LIBFT	=	lib/libft.a
MLX		=   includes/mlx.h


SRCS	=	src/main.c src/vectors.c
SRCS	+=	src/mlx/mlx_1.c src/mlx/mlx_2.c
SRCS	+=	src/parsing/parsing.c src/parsing/getline.c src/parsing/map.c src/parsing/utils.c
SRCS	+=	src/render/render.c src/render/minimap.c src/render/utils.c src/render/raycast.c
OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -rf

UNAME_S	:=	$(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LFLAGS	= -lXext -lX11 -lm -lz -Llib -lft -lmlx
endif
ifeq ($(UNAME_S), Darwin)
	LFLAGS	= -framework OpenGL -framework AppKit -Llib -lft -lmlx
endif
CFLAGS	=	-Werror -Wall -Wextra -O3 -ffast-math -funsafe-math-optimizations
	
%.o:%.c
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		$(NAME)

$(VERBOSE).SILENT:

$(LIBFT):
		bash -c "if [[ ! -d "libft" ]]; then git clone  \
			https://git.narnaud.net/nicolas-arnaud/Libft.git libft; fi"
		${MAKE} -C libft/
		cp libft/libft.a lib/
		cp libft/libft.h includes/

$(MLX):
		bash -c "if [[ ! -d "mlx" ]]; then git clone  \
			https://github.com/42Paris/minilibx-linux.git mlx; fi"
		${MAKE} -C mlx/
ifeq ($(UNAME_S), Linux)
		cp mlx/libmlx_Linux.a lib/libmlx.a
endif
ifeq ($(UNAME_S), Darwin)
		cp mlx/libmlx.a lib/
endif
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
		${RM} lib/libft.a
		${RM} includes/libft.h
		${RM} lib/libmlx.a
		${RM} includes/mlx.h
		echo Cleaning binary...
		${RM} ${NAME}
		echo ✅

re:			fclean all

.PHONY:		all clean fclean re debug
