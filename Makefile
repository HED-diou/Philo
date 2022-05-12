CC =  cc -g -c

CFLAGS = -Wall -Werror -Wextra 

SRCS =	philo.c \
		ft_atoi.c \
		utils1.c \
		timestamp.c \
		ft_my_usleep.c \
		routine.c


OBJS = ${SRCS:.c=.o}

ARV = ar -rcs

HEADER = philo.h

NAME = philo.a

REM = rm -f

.c.o :
	$(CC) $(CFLAGS) $< -o $@
	$(ARV) $(NAME) $@

all : $(NAME)
$(NAME) : $(OBJS)
	cc $(CFLAGS) ${NAME} philo.c -o philo

clean :
	${REM} ${OBJS} ${OBJS_BONUS}

fclean : clean
	${REM} ${NAME}
	${REM} philo

re : fclean all

.PHONY : all clean fclean re