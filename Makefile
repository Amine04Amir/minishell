NAME = minishell

SRC = ./src/main.c \
		./src/lexer.c \
		./src/parser.c \
		./src/syntax_error/syntax.c \
		./src/syntax_error/syntax_1.c \
		./src/builtins/builtins.c\
		./src/builtins/env.c \
		./src/builtins/echo.c \
		./src/builtins/cd.c \
		./src/builtins/cd_functions.c \
		./src/builtins/export/export.c \
		./src/builtins/export/export_helpers.c \
		./src/builtins/export/export_helpers_2.c \
		./src/builtins/export/export_helpers_3.c \
		./src/builtins/unset.c \
		./src/expand/expand.c \
		./src/expand/expand_1.c \
		./src/expand/expand_2.c \
		./src/expand/expand_3.c \
		./src/run_cmd.c \
		./src/run_heredoc.c \
		./src/signal_handler.c \
		./utils/linked_list/ft_lstaddback.c \
		./utils/linked_list/ft_env_addback.c \
		./utils/linked_list/ft_cmd_addback.c \
		./utils/linked_list/ft_file_addback.c \
		./utils/linked_list/ft_heredoc_addback.c \
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
		./utils/linked_list/ft_heredoc_new.c \
		./utils/libft/ft_strdup.c \
		./utils/libft/ft_strlcat.c \
		./utils/libft/ft_strlcpy.c \
		./utils/libft/ft_split.c \
		./utils/libft/ft_strncmp.c \
		./utils/libft/ft_strnstr.c \
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

CC = cc $(INC)
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
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
