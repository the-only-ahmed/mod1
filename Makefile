# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/19 00:49:21 by jyim              #+#    #+#              #
#    Updated: 2015/03/11 19:14:20 by jyim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  mod1

INCLUDE_DIR = includes
SRC_DIR = srcs
SRC = main.cpp Parse.cpp SceneOpenGL.cpp Volcan.cpp Water.cpp \
		gougoutte_glass.cpp tools/Vector3.class.cpp

FLAGS = -Wall -Wextra -Werror -I INCLUDE_DIR

OPENGL = -F ~/Library/Frameworks -framework \
			SDL2 -I ~/Library/Frameworks/SDL2.framework/Headers -framework OpenGL

all: $(NAME)

$(NAME):
	g++ $(FLAGS) $(OPENGL) $(SRC_DIR)/$(SRC) -o $(NAME)
	@echo "\033[32mCompiling ...\033[00m"

clean:
	@echo "\033[35mCleaning ...\033[00m"

fclean: clean
	/bin/rm -f $(NAME)
	@echo "\033[35mDeleting ...\033[00m"

re: fclean all

.PHONY: all clean fclean re
