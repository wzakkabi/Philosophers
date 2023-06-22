NAME = philo

SRC = philo.c main.c helper.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror #-fsanitize=thread

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(SRC) -o $(NAME)
%.o : %.c
	gcc $(FLAGS) -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
