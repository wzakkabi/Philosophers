NAME = philo

SRC = philo.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror 

all : $(NAME)
	./philo 5 410 200 200
$(NAME) : $(OBJ)

%.o : %.c
	gcc -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
