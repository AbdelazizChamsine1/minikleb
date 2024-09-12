NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra
SRCS = main.c load_shell.c tokens.c tokens_utils.c\
		get_env.c env.c shlvl.c expansions1.c expansions_utils.c\
		env_fuc.c export_fuc.c print_sort.c unset_fuc.c pwd_fuc.c\
		cd_fuc.c cd_file.c env_init_secret.c cd_env.c expansions.c\
		echo_fuc.c token.c bin.c free.c fd.c

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
