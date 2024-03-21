UNAME		:=	$(shell uname)

NAME		=	cub3D

# PROGRAMS #

CC			=	cc
RM			=	rm

# DIRECTORIES #

SRC_DIR		=	src
BUILD_DIR	=	build
SUB_DIRS	=	parsing utils hud

LIBFT_DIR	=	libs/libft
MLX_DIR		=	libs/MLX42
MLX_BUILD	=	$(MLX_DIR)/build

# FLAGS #

CFLAGS_MoS		=	-Wall -Wextra -Werror -MMD -g3 -fsanitize=address
CFLAGS_LX		=	-Wall -Wextra -Werror -Wunreachable-code -Ofast -g3 -fsanitize=address

MLXFLAGS_MoS	=	-lglfw -framework Cocoa -framework OpenGL -framework IOKit
MLXFLAGS_LX 	=	-ldl -lglfw -pthread -lm
RMFLAGS			=	-rf
INCFLAGS		=	-I./include \
					-I./$(LIBFT_DIR)/include \
					-I./$(MLX_DIR) \
					-I./$(MLX_DIR)/include/MLX42

# FILES #

SRCS		=	$(SRC_DIR)/main.c \
				$(foreach dir, $(SUB_DIRS), $(wildcard $(SRC_DIR)/$(dir)/*.c))
OBJS		=	$(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
DEPS		=	$(OBJS:.o=.d)

# ARCHIVES #

LIBFT		=	$(LIBFT_DIR)/libft.a
MLX42		=	$(MLX_BUILD)/libmlx42.a

# RULES #

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
ifeq ($(UNAME), Linux)
	$(CC) $(OBJS) $(CFLAGS_LX) $(INCFLAGS) $(LIBFT) $(MLX42) $(MLXFLAGS_LX) -o $@
else ifeq ($(UNAME), Darwin)
	$(CC) $(CFLAGS_MoS) $(INCFLAGS) $(LIBFT) $(MLX42) $(MLXFLAGS_MoS) -o $@ $(OBJS)
else
	$(error Unsuported operating system: $(UNAME))
endif

$(LIBFT):
	@echo "\033[38;5;214m-----Compiling the LIBFT files-----"
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		git submodule add -f https://github.com/nnavidd/Libft.git $(LIBFT_DIR); \
	fi
	@mkdir -p $(LIBFT_DIR)
	@git submodule update --init --recursive --remote $(LIBFT_DIR)
	@make -C $(LIBFT_DIR) --silent

$(MLX42):
	@echo "\033[38;5;214m-----Compiling the MLX files-----"
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git submodule add -f https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@git submodule update --init --recursive --remote $(MLX_DIR)
ifeq ($(UNAME), Linux)
	@cmake -S $(MLX_DIR)/ -B $(MLX_BUILD) -DGLFW_FETCH=1
	@make -C $(MLX_BUILD) -j4
else ifeq ($(UNAME), Darwin)
	@brew install glfw
	@cmake $(MLX_DIR) -B $(MLX_BUILD) && make -C $(MLX_BUILD) -j4
endif
-include $(DEPS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
ifeq ($(UNAME), Linux)
	$(CC) $(CFLAGS_LX) $(INCFLAGS) -c $< -o $@
else ifeq ($(UNAME), Darwin)
	$(CC) $(CFLAGS_MoS) $(INCFLAGS) -c $< -o $@
endif

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(BUILD_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

libclean:
	$(RM) $(RMFLAGS) $(LIBFT_DIR) $(MLX_DIR)

allclean: libclean fclean

libupdate: libclean all

.PHONY: all clean fclean re libclean allclean libupdate
