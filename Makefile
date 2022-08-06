# CFLAGS = -Wall -Wextra -Werror
CFLAGS = 
CPPFLAGS = -I includes
NAME = so_long
SRCS = main.c ft_strjoin.c
OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))
OBJDIR = obj
VPATH = srcs

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) minilibx-linux/libmlx_Darwin.a -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all