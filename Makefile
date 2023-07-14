# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 15:41:41 by fabperei          #+#    #+#              #
#    Updated: 2023/07/13 10:31:46 by fabperei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = $(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[34mCompiling $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "\033[32m$(NAME) compiled\033[0m"

.c.o:
	@echo "\033[34mCompiling $<...\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "\033[33mCleaning object files...\033[0m"
	@rm -f $(OBJS)
	@echo "\033[33mObject files cleaned.\033[0m"

fclean: clean
	@echo "\033[33mCleaning $(NAME)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[33m$(NAME) cleaned.\033[0m"

re: fclean all

.PHONY: all clean fclean re
