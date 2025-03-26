FCT = src/main.c\
		src/Parting.c\
		src/utils.c
OBJ = ${FCT:.c=.o}

ALL = ${FCT}

OBJB = ${ALL:.c=.o}

CC = cc

CFLAG = -Wall -Wextra -Werror -IIncludes

NAME = philo.a

all : ${NAME}

${NAME} : ${OBJ}
	ar rcs $@ $^

%.o : %.c
	${CC} ${CFLAG} $^ -c -o $@

clean :
	rm -rf ${OBJB}

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY : fclean clean all re
