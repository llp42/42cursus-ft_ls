NAME     = ft_ls

CC       = cc
CFLAGS   = -Wall -Wextra -Werror

SRCS     = src/main.c
OBJS     = $(SRCS:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	$(RM) -r obj

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
