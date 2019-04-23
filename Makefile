# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: conoel <conoel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 21:14:13 by conoel            #+#    #+#              #
#    Updated: 2019/04/23 15:32:17 by conoel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
HEADER = include/lem_in.h
AUTEUR = "conoel\nbghandou"

SRC_NAME =	main.c\
			verify_data.c\
			load_data.c\
			load_structure.c\
			alloc_links_list.c\
			node_creation.c\
			free_nodes.c\
			node_utils.c\
			path_utils.c\
			basic_solver.c\
			closed_room.c\
			bfs.c\
			choose_path.c\
			count_edges.c\
			print_test.c\
			travel_flux.c\
			display_end.c\
			display_end_visu.c

SRC_DIR = ./src/
SRC = ${addprefix $(SRC_DIR), $(SRC_NAME)}

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_DIR = ./obj/
OBJ = ${addprefix $(OBJ_DIR), $(OBJ_NAME)}

HEADER_DIR = ./include/
HEADER_NAME =	lem_in.h\
				visu.h
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
	@echo "\n \033[1m\033[4m\033[35m\\^/ Done compiling \\^/\033[0m [$(NAME)] --> $(LIB_NAME)"
	@echo "#####################################################"
	@echo "#####################################################  /-----~~-----\\"
	@echo "####   _      ____   _     _         _   _    _  ####  |  BGHANDOU  |"
	@echo "####  | |    |  __| | \   / |       |_| |  \ | | ####  \-----~~-----/"
	@echo "####  | |    | |__  |  \_/  |  ___   _  |   \| | ####"
	@echo "####  | |    |  __| | |\_/| | |___| | | | |\   | ####"
	@echo "####  | |__  | |__  | |   | |       | | | | \  | ####"
	@echo "####  |____| |____| |_|   |_|       |_| |_|  |_| ####    /---~~---\\"
	@echo "####                                             ####    | CONOEL |"
	@echo "#####################################################    \---~~---/"
	@echo "#####################################################"
# Oui j'ai passê 20 minutes a faire ca et oui je suis un putain d'autiste
# Heil Anne Frank


$(OBJ_DIR):
	@clear
	@mkdir $(OBJ_DIR)
	@echo "\n>=========== * \033[32m\033[1mCreating $(NAME) obj dir\033[0m * ===========<";

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@ -I$(HEADER_DIR) -I$(LIB_HEADER) `sdl2-config --cflags`
	@printf "\033[32m\033[1m\033[4mCompiling\033[0m\033[32m : %-30s \033[0m [$(NAME)]\n" $@

./auteur:
	@echo $(AUTEUR) > ./auteur
	@echo "\033[32m<Created Author file>\033[0m"

############# LIB #############

$(LIB):
	@make -C $(LIB_DIR)
