# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 22:22:02 by antonsplavn       #+#    #+#              #
#    Updated: 2024/12/01 00:09:03 by antonsplavn      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I include

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Subdirectories inside src
UTILS_DIR = $(SRC_DIR)/utils
PARSING_DIR = $(SRC_DIR)/parsing

# Source Files
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(UTILS_DIR)/*.c) \
       $(wildcard $(PARSING_DIR)/*.c)

# Object Files (output in obj/)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, \
	   $(patsubst $(UTILS_DIR)/%.c, $(OBJ_DIR)/%.o, \
	   $(patsubst $(PARSING_DIR)/%.c, $(OBJ_DIR)/%.o, \
	   $(SRCS))))

# Output Binary Name
NAME = philosophers

# Default Rule
all: $(NAME)

# Linking the Binary
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compiling Each Source File to an Object File
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSING_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Object Files
clean:
	rm -rf $(OBJ_DIR)

# Clean Everything
fclean: clean
	rm -f $(NAME)

# Rebuild Everything
re: fclean all
