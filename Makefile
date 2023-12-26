# Program name
NAME = pipex

# Colors
DEFAULT    = \033[0m
BLACK    = \033[0;30m
RED        = \033[0;31m
GREEN    = \033[0;32m
YELLOW    = \033[0;33m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
CYAN    = \033[0;36m
BWHITE    = \033[1;37m

# Directories
LIB_DIR = lib
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIBFT_DIR = lib/libft
LIBMLX_DIR = lib/minilibx

# Files
LIBFT = $(LIBFT_DIR)/libft.a

define LIB :=
	$(LIBFT)
endef
LIB := $(strip $(LIB))

define INCLUDE :=
	$(INC_DIR)
	$(LIBFT_DIR)/include
endef
INCLUDE := $(strip $(INCLUDE))

define SRC :=
	check_wstatus.c
	close_and_free.c
	close_pipes.c
	errors.c
	exec_child.c
	init_controls.c
	init_fd.c
	main.c
	redirect_fd.c
endef
SRC := $(strip $(SRC))

OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# Utils
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf
INCLUDE_FLAGS := $(addprefix -I , $(INCLUDE))
LIB_FLAGS = --no-print-directory --silent

# Rules
.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo "$(RED)! Removing$(DEFAULT) $(OBJ_DIR) files"
	@$(RM) $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)

.PHONY: re
re: fclean all

$(LIBFT):
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) $(LIB_FLAGS)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"

.PHONY: cleanlib
cleanlib:
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make clean -C $(LIBFT_DIR) $(LIB_FLAGS)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"

.PHONY: fcleanlib
fcleanlib:
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make fclean -C $(LIBFT_DIR) $(LIB_FLAGS)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"

.PHONY: relib
relib: fcleanlib $(LIBFT)

.PHONY: norm
norm:
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) norm $(LIB_FLAGS)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"
	@norminette $(SRC_DIR) $(INC_DIR) | awk '/'Error'/ {print; found=1} END {if (!found) print "$(PURPLE)Norm OK$(DEFAULT)"}'
