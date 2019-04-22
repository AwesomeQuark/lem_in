# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: conoel <conoel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 21:14:13 by conoel            #+#    #+#              #
#    Updated: 2019/04/22 17:44:01 by conoel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visu
AUTEUR = "conoel\n"

SRC_NAME =	main.c\
			lexer.c\
			token_manipulation.c\
			sdl_utils.c\

SRC_DIR = ./src/
SRC = ${addprefix $(SRC_DIR), $(SRC_NAME)}

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_DIR = ./obj/
OBJ = ${addprefix $(OBJ_DIR), $(OBJ_NAME)}

HEADER_DIR = ./include/
HEADER_NAME = $(NAME).h
HEADER = ${addprefix $(HEADER_DIR), $(HEADER_NAME)}

LIB_NAME = haflib.a
LIB_DIR = ./haflib/
LIB_HEADER = ./haflib/includes/
LIB = ${addprefix $(LIB_DIR), $(LIB_NAME)}

FLAGS = #-Wall -Werror -Wextra -Ofast
CC = clang

#################################################################################
##################################### RULES #####################################
#################################################################################

########## GENERALS ##########

.PHONY: all clean fclean re

all: $(LIB) $(OBJ_DIR) $(NAME)

re: fclean all

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)

fclean:
	@make fclean -C $(LIB_DIR)
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo "\033[31m\033[1m\033[4mCleaning\033[0m\033[31m : Everything\033[0m [$(NAME)]";

######### COMPILATION #########

$(NAME): ./auteur $(OBJ_DIR) $(OBJ) $(HEADER)
	@$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME) -I$(HEADER_DIR) -I$(LIB_DIR) `sdl2-config --cflags --libs`
	@echo "\n \033[1m\033[4m\033[35m\\^/ Done compilate \\^/\033[0m [$(NAME)] --> $(LIB_NAME)"


$(OBJ_DIR):
	@clear
	@mkdir $(OBJ_DIR)
	@echo "\n>=========== * \033[32m\033[1mCreating $(NAME) obj dir\033[0m * ===========<";

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@ -I$(HEADER_DIR) -I$(LIB_HEADER) `sdl2-config --cflags`
	@printf "\033[32m\033[1m\033[4mCompilating\033[0m\033[32m : %-30s \033[0m [$(NAME)]\n" $@

./auteur:
	@echo $(AUTEUR) > ./auteur
	@echo "\033[32m<Created Author file>\033[0m"

############# LIB #############

$(LIB):
	@make -C $(LIB_DIR)