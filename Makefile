### PROGRAM NAME ###
NAME = pipex

### COLORS ###
DEFAULT    	:= \033[0m
BLACK    	:= \033[0;30m
RED        	:= \033[0;31m
GREEN    	:= \033[0;32m
YELLOW    	:= \033[0;33m
BLUE    	:= \033[0;34m
PURPLE    	:= \033[0;35m
CYAN    	:= \033[0;36m
BWHITE    	:= \033[1;37m

### DIRECTORIES ###
LIBS_DIR	:= libs
SRC_DIR		:= srcs
INCLD_DIR	:= includes
OBJS_DIR	:= objs
LIBFT_DIR	:= $(LIBS_DIR)/libft

### FILES ###
LIBFT = $(LIBFT_DIR)/libft.a

define LIB :=
	$(LIBFT)
endef
LIB := $(strip $(LIB))

define INCLUDES :=
	$(INCLD_DIR)
	$(LIBFT_DIR)/includes
endef
INCLUDES := $(strip $(INCLUDES))

define SRC :=
	main.c
	utils.c
endef
SRC := $(strip $(SRC))

OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))

# Utils
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf
INCLD_DIR := $(addprefix -I , $(INCLUDES))
LIB_FLAGS = --no-print-directory --silent

# Rules
.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLD_DIR) -c $< -o $@

.PHONY: clean
clean:
	@echo "$(RED)! Removing$(DEFAULT) $(OBJS_DIR) files"
	@$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)

.PHONY: re
re: fclean all

$(LIBFT):
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@git submodule update
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

### NORM ###
.PHONY: norm
norm:
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) norm $(LIB_FLAGS)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"
	@norminette $(SRC_DIR) $(INCLUDES) | awk '/Error/ {print; found=1} END \
	{if (!found) {print "$(PURPLE)Norm OK$(DEFAULT)"; exit 0 }; exit 1 }'