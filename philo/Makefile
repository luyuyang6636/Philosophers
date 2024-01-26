SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -f

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
all: $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re