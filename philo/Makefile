# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 14:53:08 by krazikho          #+#    #+#              #
#    Updated: 2024/10/14 13:15:43 by krazikho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

NAME_SRCS = main.c parsing.c utils.c create_table.c create_philos.c one_philo.c \
			more_philos.c clean.c monitor.c ph_atoi.c

NAME_OBJS = $(NAME_SRCS:.c=.o)


all: $(NAME)

$(NAME): $(NAME_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(NAME_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(NAME_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re