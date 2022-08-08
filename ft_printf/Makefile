CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I ft_printf.h
NAME = libftprintf.a
SRCS = ft_printf.c utils.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) r $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all