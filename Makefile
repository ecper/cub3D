# プロジェクトの設定
NAME = Cub3D
GNL = $(wildcard get_next_line/*.c) # 後で修正
LIB_DIR		= ./Libft
LIB_NAME	= $(LIB_DIR)/libft.a
SRC = srcs/main.c srcs/global.c srcs/init.c srcs/free.c srcs/event.c srcs/utils.c srcs/vector.c srcs/ray.c srcs/render.c srcs/readfile.c\
srcs/parser.c srcs/parser_util.c srcs/parser_path.c srcs/parser_color.c srcs/line_util.c srcs/error.c srcs/map.c srcs/map_util.c srcs/map_surround.c $(GNL) $(LIB_NAME)
OBJS = $(SRC:%.c=%.o)

# MiniLibX のパス
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# コンパイルフラグ
INCLUDES = -I includes -g
CFLAGS = -O3 $(INCLUDES)
LDFLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -g
# -fsanitize=address

# コンパイラ
CC = cc

# ビルドターゲット
all: $(MLX) $(NAME) $(LIB_NAME)

$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

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
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

# テストターゲット
.PHONY: all clean fclean re