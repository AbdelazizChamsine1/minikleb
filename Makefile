NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I.  # Add the current directory to the include path

SRCS = main.c \
       load_shell.c \
       builtin/cd_file.c \
       builtin/cd_fuc.c \
       builtin/echo_fuc.c \
       builtin/env_fuc.c \
       builtin/export_fuc.c \
       builtin/pwd_fuc.c \
       builtin/shlvl.c \
       builtin/unset_fuc.c \
       env/env_init_secret.c \
       env/env.c \
       env/get_env.c \
       expansion/expansions_utils.c \
       expansion/expansions.c \
       expansion/expansions1.c \
       redir/bin.c \
       redir/pipe_divide.c \
       redir/red_divide.c \
       redir/Redirections.c \
       token/token.c \
       token/tokens_utils.c \
       utils/fd.c \
       utils/free.c \
       utils/type.c \
       exec.c  # Removed the duplicate load_shell.c

LDFLAGS = -lreadline
LIBFT = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

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
