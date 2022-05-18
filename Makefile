# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 21:09:53 by gcollet           #+#    #+#              #
#    Updated: 2022/05/18 18:30:58 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	ft_containers

INC_PATH		=	includes/
OBJS_PATH		=	obj/

RED				=	\033[31;1m
YELLOW			=	\033[93;1m
GREEN			=	\033[32;1m
BLUE			=	\033[34;1m
END				=	\033[0m

CC 				=	clang++
CFLAGS			=	-Wall -Werror -Wextra -std=c++98

RM				=	rm -rf

SRCS_FILES		=	main.cpp

OBJS_FILES		= 	$(SRCS_FILES:.cpp=.o)
#OBJS 			=	$(addprefix $(OBJS_PATH), $(OBJS_FILES))
OBJS 			=	/home/gcollet/ft_containers/tests/main_map.cpp

$(OBJS_PATH)%.o: %.cpp
	@$(CC) $(CFLAGS) -I$(INC_PATH) -c $< -o $@
	@echo "$(YELLOW) CREATING OBJECTS \n $(END)"

$(NAME):	$(OBJS_PATH) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -Ift_containers_tester/tests -Iincludes
	@echo "\033[32;1m TESTER READY \033[0m \\n"

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

all:	$(NAME)

debug:	CFLAGS += -g
debug:	$(NAME)

clean:
	@$(RM) $(OBJS_FILES) $(OBJS_PATH) 
	@echo "\\n$(RED) CLEAN DONE $(END)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED) FCLEAN DONE $(END)\\n"

re: fclean all

redebug: fclean debug

.PHONY: all clean fclean re debug redebug
