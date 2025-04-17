
# Nom de l'exécutable
NAME = philo

# Compilateur et options
CC = cc
HEADER = Includes/
CFLAGS = -Wall -Wextra -Werror -I ${HEADER}

# Fichiers sources et objets
SRCS =	src/main.c\
		src/Parting.c\
		src/utils.c
OBJS = $(SRCS:.c=.o)
# Commandes
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
