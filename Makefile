# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: conoel <conoel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 21:14:13 by conoel            #+#    #+#              #
#    Updated: 2019/03/19 18:36:16 by conoel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
HEADER = include/lem_in.h
AUTEUR = "conoel\nbghandou"

SRC_NAME =	main.c\
			verify_data.c\
			load_data.c\
			load_structure.c\
			node_creation.c\
			free_nodes.c\
			node_utils.c\
			solver.c\

SRCDIR = ./src/
SRC = ${addprefix $(SRCDIR), $(SRC_NAME)}

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJDIR = ./obj/
OBJ = ${addprefix $(OBJDIR), $(OBJ_NAME)}

LIB_NAME = haflib.a
LIB_DIR = ./haflib/
LIB = ${addprefix $(LIB_DIR), $(LIB_NAME)}

FLAGS = -Wall -Werror -Wextra -Ofast
CC = clang

#################################################################################
##################################### RULES #####################################
#################################################################################

########## GENERALS ##########

.PHONY: all clean fclean re

all: $(LIB) $(OBJDIR) $(NAME)

re: fclean all

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIB_DIR)

fclean:
	@make fclean -C $(LIB_DIR)
	@rm -rf $(OBJDIR) $(NAME)
	@echo "\033[31m\033[1m\033[4mCleaning\033[0m\033[31m : Everything\033[0m [$(NAME)]";

######### COMPILATION #########

$(NAME): ./auteur $(OBJDIR) $(OBJ) $(HEADER)
	@$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo "\n \033[1m\033[4m\033[35m\\^/ Done compilate \\^/\033[0m [$(NAME)] --> $(LIB_NAME)"
	@echo "#######################################################"
	@echo "#######################################################  /------------\\"
	@echo "####   _      ____   _     _           _   _    _  ####  |  BGHANDOU  |"
	@echo "####  | |    |  __| | \   / |         |_| |  \ | | ####  \------------/"
	@echo "####  | |    | |__  |  \_/  |          _  |   \| | ####"
	@echo "####  | |    |  __| | |\_/| |         | | | |\   | ####"
	@echo "####  | |__  | |__  | |   | |  _____  | | | | \  | ####"
	@echo "####  |____| |____| |_|   |_| |_____| |_| |_|  |_| ####   /--------\\"
	@echo "####                                               ####   | CONOEL |"
	@echo "#######################################################   \--------/"
	@echo "#######################################################"
# Oui j'ai passê 20 minutes a faire ca et oui je suis un putain d'autiste
# Heil Anne Frank


$(OBJDIR):
	@clear
	@mkdir $(OBJDIR)
	@echo "\n>=========== * \033[32m\033[1mCreating $(NAME) obj dir\033[0m * ===========<";

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\033[32m\033[1m\033[4mCompilating\033[0m\033[32m : %-30s \033[0m [$(NAME)]\n" $@

./auteur:
	@echo $(AUTEUR) > ./auteur
	@echo "\033[32m<Created Author file>\033[0m"

############# LIB #############

$(LIB):
	@make -C $(LIB_DIR)


