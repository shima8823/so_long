# CFLAGS = -Wall -Wextra -Werror
CFLAGS = 
CPPFLAGS = -I includes
NAME = so_long
SRCS = main.c get_next_line.c get_next_line_utils.c
OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))
OBJDIR = obj
VPATH = srcs

## libft ##
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
###########

## printf ##
PRINTF_DIR = ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
############


all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF) minilibx-linux/libmlx_Darwin.a -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(PRINTF)
	$(RM) $(NAME)

re: fclean all