CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I libft.h
NAME = libft.a
SRCS =	ft_bzero.c		\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_memset.c		\
		ft_isalpha.c	\
		ft_isdigit.c	\
		ft_strlen.c		\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_atoi.c		\
		ft_memcmp.c		\
		ft_strncmp.c	\
		ft_strrchr.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_memchr.c		\
		ft_strchr.c		\
		ft_strnstr.c	\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_split.c		\
		ft_itoa.c		\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c

BONUS_SRCS =	ft_lstnew_bonus.c		\
				ft_lstadd_front_bonus.c	\
				ft_lstsize_bonus.c		\
				ft_lstlast_bonus.c		\
				ft_lstadd_back_bonus.c	\
				ft_lstdelone_bonus.c	\
				ft_lstclear_bonus.c		\
				ft_lstiter_bonus.c		\
				ft_lstmap_bonus.c

OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

ifdef WITH_BONUS
OBJS += ${BONUS_OBJS}
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) r $(NAME) $(OBJS)
bonus:
	@make WITH_BONUS=1
clean:
	$(RM) $(OBJS) ${BONUS_OBJS}
fclean: clean
	$(RM) $(NAME)
re: fclean all