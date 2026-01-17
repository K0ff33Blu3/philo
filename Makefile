NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR)

# DIRECTORIES
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC := $(shell find $(SRC_DIR) -name "*.c")

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo -e "\033[32m✔ $(NAME) created successfully\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "\033[90m• Compiled $<\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "\033[33m✘ $(NAME) object files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo -e "\033[33m✘ Executables removed\033[0m"

re: fclean all

.PHONY: all bonus clean fclean re

