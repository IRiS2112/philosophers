# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 14:56:11 by hakaraou          #+#    #+#              #
#    Updated: 2024/04/18 18:33:41 by hakaraou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

B_NAME = philo_bonus

B_SRC = get_data_bonus.c pars_bonus.c philo_bonus.c philo_utils_bonus.c routine_bonus.c libft_bonus.c libft2_bonus.c

B_OBJ = $(B_SRC:.c=.o)

all : $(B_NAME)

$(B_NAME) : $(B_OBJ)
	$(CC) $(CFLAGS) $(B_OBJ) -o $(B_NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -f $(B_OBJ)

fclean : clean
	rm -f $(B_NAME)

re : fclean all

.PHONY : all clean flcean re