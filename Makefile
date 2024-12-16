NAME = minishell

SRC = ./src/main.c \
		./src/lexer.c \
		./src/syntax_error/syntax.c \
		./src/syntax_error/syntax_1.c \
		./src/expand/expand.c \
		./src/parser.c \
		./src/run_heredoc.c \
		./src/executer.c \
		./src/signal_handler.c \
		./src/exit_handler.c \
		./src/builtins/builtins.c\
		./src/builtins/env/env.c \
		./src/builtins/echo/echo.c \
		./src/builtins/echo/echo_1.c \
		./src/builtins/cd/cd.c \
		./src/builtins/cd/cd_functions.c \
		./src/builtins/exit/exit.c \
		./src/builtins/exit/exit_1.c \
		./src/builtins/export/export.c \
		./src/builtins/export/export_1.c \
		./src/builtins/export/export_2.c \
		./src/builtins/export/export_3.c \
		./src/builtins/unset.c \
		./utils/garbage.c\
		./utils/linked_list/ft_lstaddback.c \
		./utils/linked_list/ft_env_addback.c \
		./utils/linked_list/ft_cmd_addback.c \
		./utils/linked_list/ft_file_addback.c \
		./utils/linked_list/ft_lstaddfront.c \
		./utils/linked_list/ft_lstsize.c \
		./utils/linked_list/ft_envsize.c \
		./utils/linked_list/ft_lstmax.c \
		./utils/linked_list/ft_lstmin.c \
		./utils/linked_list/ft_lstdisplay.c \
		./utils/linked_list/ft_lstclear.c \
		./utils/linked_list/ft_env_clear.c \
		./utils/linked_list/ft_lstnew.c \
		./utils/linked_list/ft_env_new.c \
		./utils/linked_list/ft_cmd_new.c \
		./utils/linked_list/ft_file_new.c \
		./utils/libft/ft_strdup.c \
		./utils/libft/ft_strlcat.c \
		./utils/libft/ft_strlcpy.c \
		./utils/libft/ft_strncpy.c \
		./utils/libft/ft_split.c \
		./utils/libft/ft_strncmp.c \
		./utils/libft/ft_strcmp.c \
		./utils/libft/ft_strcat.c \
		./utils/libft/ft_strcpy.c \
		./utils/libft/ft_strnstr.c \
		./utils/libft/ft_strtrim.c \
		./utils/libft/ft_substr.c \
		./utils/libft/ft_isspace.c \
		./utils/libft/ft_strlen.c \
		./utils/libft/ft_strchr.c \
		./utils/libft/ft_putstr_fd.c \
		./utils/libft/ft_putchar_fd.c \
		./utils/libft/ft_ssplit.c \
		./utils/libft/ft_isalnum.c \
		./utils/libft/ft_isalpha.c \
		./utils/libft/ft_strjoin.c \
		./utils/libft/ft_memcpy.c \
		./utils/libft/ft_calloc.c \
		./utils/libft/ft_bzero.c \
		./utils/libft/ft_memmove.c \
		./utils/libft/ft_memset.c \
		./utils/libft/ft_atoi.c \
		./utils/libft/ft_itoa.c \
		./utils/libft/ft_isdigit.c \

CC = cc $(INC)
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
OBJ = $(SRC:.c=.o)
INC = -I./includes/

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

sup:
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

.SECONDARY: $(OBJ)
