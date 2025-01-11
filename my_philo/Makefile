NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -Iincludes -Ilibft/inc

LIBFT_PATH = libft
LIBFT_LIB = -L$(LIBFT_PATH) -lft

CFILES = src/main.c \
         utils/init.c \
         utils/utils.c \
         utils/threads.c \
         utils/actions.c

OBJECTS = $(CFILES:.c=.o)

all: libraries $(NAME)

libraries:
	@$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_LIB) -o $(NAME)
	@echo "Compilation réussie : $(NAME)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilé : $<"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -f $(OBJECTS)
	@echo "Nettoyage terminé."

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "Suppression de $(NAME) et des objets."

re: fclean all

.PHONY: all libraries clean fclean re
