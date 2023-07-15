# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/09 20:59:48 by abelfany          #+#    #+#              #
#    Updated: 2023/07/15 07:59:25 by abelfany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = philosophers_bonus.h
NAME = philo_bonus

SRC_M = philosophers_bonus.c \
		ft_atoi_bonus.c \
		helper_bonus.c \
		ph_generator_bonus.c \
		extontion_bonus.c \

OBJ_M = $(SRC_M:.c=.o)
C_FLAG = -Wall -Wextra -Werror 
RM = @rm -rf

all: $(NAME)
	@echo "                 \033[1;31m BY abelfany \033[0m"

$(NAME):$(OBJ_M)
	cc $(C_FLAG) $(OBJ_M) -o $(NAME)

%.o : %.c $(HEADER)
	cc $(C_FLAG) -c $< -I $(HEADER) -o $@

clean : 
	$(RM) $(OBJ_M)

fclean : clean
	$(RM) $(NAME)

re : fclean all

trash : 
	$(RM) a.out && mv test.c .test.c

.PHONY : all fclean clean re
