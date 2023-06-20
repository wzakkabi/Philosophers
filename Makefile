NAME = philo

SRC = philo.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror  #-g -fsanitizer=thread

all : $(NAME)
	
$(NAME) : $(OBJ)

%.o : %.c
	gcc -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
