# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 21:09:53 by gcollet           #+#    #+#              #
#    Updated: 2022/06/11 15:47:32 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	ft_containers

INC_PATH		=	includes/
OBJS_PATH		=	tests/obj/
OUTPUT_PATH		=	tests/output/
DIFF_PATH		=	tests/diff/
LOG_PATH		=	tests/log/

RED				=	\033[31;1m
YELLOW			=	\033[93;1m
GREEN			=	\033[32;1m
BLUE			=	\033[34;1m
END				=	\033[0m

CC 				=	clang++
CFLAGS			=	-Wall -Werror -Wextra -std=c++98
NAMESPACE		=	ft

RM				=	rm -rf

SRCS_FILES		=	set.cpp
FT_OUTPUT		=	$(OUTPUT_PATH)ft.out
STD_OUTPUT		= 	$(OUTPUT_PATH)std.out
DIFF_OUTPUT   	=	$(OUTPUT_PATH)diff.out

OBJS_FILES		= 	$(SRCS_FILES:.cpp=.o)
OBJS 			=	$(addprefix $(OBJS_PATH), $(OBJS_FILES))

$(OBJS_PATH)%.o: %.cpp
	$(CC) $(CFLAGS) -DNAMESPACE=$(NAMESPACE) -I$(INC_PATH) -c $< -o $@
	@echo "$(YELLOW) CREATING OBJECTS \n $(END)"

$(NAME):	$(OBJS_PATH) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -Iincludes
	@echo "$(GREEN) TESTER READY $(END)\n"

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

VPATH = tests

all:	$(NAME)

debug:	CFLAGS += -g
debug:	$(NAME)

clean:
	$(RM) $(OBJS_FILES) $(OBJS_PATH) 
	echo "$(RED) CLEAN DONE $(END)\\n"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OUTPUT_PATH)
	$(RM) $(DIFF_PATH)
	$(RM) $(LOG_PATH)
	$(RM) err.log
	echo "$(RED) FCLEAN DONE $(END)\\n"

re: fclean all

redebug: fclean debug

star-wars:
	telnet towel.blinkenlights.nl

# test: NAMESPACE = std
# test: fclean $(NAME)
# 	mkdir -p $(OUTPUT_PATH)
# 	./$(NAME) > $(STD_OUTPUT)
# 	$(MAKE) -B
# 	./$(NAME) > $(FT_OUTPUT)
# 	diff -u $(FT_OUTPUT) $(STD_OUTPUT) > $(DIFF_OUTPUT) || exit 0
# 	@if [ -s $(DIFF_OUTPUT) ]; then\
# 		echo "$(RED)======TEST FAILED======$(END) (Check tests/output/diff.out for more info)";\
# 	else\
# 		echo "$(GREEN)======TEST SUCCESS======$(END)\n";\
# 	fi

.PHONY: all clean fclean re debug redebug test
