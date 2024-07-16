RM = rm -f

CFLAGS = -Wall -Werror -Wextra

SRCS = server.c client.c

OBJS = $(SRCS:.c=.o)

all: server client

server: server.o Makefile
	cc $(CFLAGS) server.c -o server

client: client.o Makefile
	cc $(CFLAGS) client.c -o client

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) server client

re: fclean all

.PHONY: all clean fclean re
