NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra
SRCS = try.c load_shell.c tokens.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
