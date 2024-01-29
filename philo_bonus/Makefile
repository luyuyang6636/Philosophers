SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
NAME = philo_bonus
RM = rm -f
CC = gcc
FLAGS = -Werror -Wextra -Wall -g

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $@
%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@
all: $(NAME)
bonus: $(NAME)
clean:
		$(RM) $(OBJS)
fclean: clean
		$(RM) $(NAME)
re: fclean all

.PHONY: all clean bonus fclean re

