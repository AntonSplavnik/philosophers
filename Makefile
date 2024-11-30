# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 22:22:02 by antonsplavn       #+#    #+#              #
#    Updated: 2024/11/30 23:03:55 by antonsplavn      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source Files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object Files (in obj/ directory)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Output Binary Name
NAME = philosophers

# Default Rule
all: $(NAME)

# Linking the Objects into the Binary
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compiling Each .c File into a .o File in obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
