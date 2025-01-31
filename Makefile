# プロジェクトの設定
NAME = Cub3D
SRC = srcs/main.c srcs/global.c srcs/init.c srcs/free.c \
 	srcs/event.c srcs/utils.c srcs/vector.c \
	srcs/render/raycasting.c srcs/render/texture.c srcs/render/render.c srcs/render/draw.c
OBJS = $(SRC:%.c=%.o)

# MiniLibX のパス
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# コンパイルフラグ
INCLUDES = -I includes
CFLAGS = -O3 $(INCLUDES) -g
LDFLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm

# コンパイラ
CC = cc

# ビルドターゲット
all: $(MLX) $(NAME)

# bonus target
bonus: $(MLX) $(NAME)

$(MLX):
	@echo "Building MiniLibX..."
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $^ -o $(NAME) $(LDFLAGS)

# オブジェクトファイルの生成
%.o: %.c
	@echo "$(CC) $(CFLAGS) -c $< -o $@"
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップターゲット
clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

# テストターゲット
.PHONY: all clean fclean re