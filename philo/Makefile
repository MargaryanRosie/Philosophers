NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = init.c \
      philosophers.c \
      routine.c \
      utils.c \
	  death_monitor.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re