NAME = philo

SRC = philo.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror  -g -fsanitize=thread

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS)  $< -o philo
%.o : %.c
	gcc $(FLAGS) -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
