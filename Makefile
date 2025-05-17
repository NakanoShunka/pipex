NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Mandatory part
MANDATORY_SRC = main.c pipex.c ft_split.c ft_strjoin.c ft_strncmp.c found_path.c free_split.c
MANDATORY_OBJ = $(MANDATORY_SRC:.c=.o)

# Bonus part
BONUS_SRC = bonus_main.c bonus_pipex.c ft_split.c ft_strjoin.c ft_strncmp.c found_path.c free_split.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Default rule
all: $(NAME)

$(NAME): $(MANDATORY_OBJ)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) -o $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


