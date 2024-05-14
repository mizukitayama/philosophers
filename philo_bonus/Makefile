CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf
AR		=	ar rcs

OBJ_DIR	=	obj/
SRC_DIR	=	src/
SRCS	=	main.c utils.c parse_input.c init.c \
				supper.c getter_setter.c synchro.c write.c clean.c monitor.c
NAME	=	philo_bonus

SRCS_OBJS	=	$(SRCS:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR), $(SRCS_OBJS))

INCLUDE	=	-I inc/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re
