NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra
SRCS = try.c load_shell.c tokens.c tokens_utils.c\
		get_env.c env.c shlvl.c

LDFLAGS = -lreadline
LIBFT = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
