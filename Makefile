# _*_ MakeFile _*_

CC = gcc

CFLAGS = -g -pthread -Wall -Wextra -Werror -fsanitize=thread

NAME = philo

SRC = main.c utils.c init.c print_msg.c philo.c

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) $(FLAGS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus