CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
SRC = ft_atoi.c \
		ft_itoa.c \
		ft_split.c \
		ft_bzero.c \
		ft_strdup.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_strcmp.c \
		ft_strchr.c \
		ft_strlen.c \
		ft_calloc.c \
		ft_substr.c \
		ft_memmove.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_putchar.c \
		ft_strtrim.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_strjoin.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putchar_fd.c \

B_SRC = ft_lstnew.c \
		ft_lstmap.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstiter.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \

OBJ = $(SRC:.c=.o) $(GNL_OBJ)
B_OBJ = $(B_SRC:.c=.o)

GNL_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

GNL_BONUS_SRC = get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
GNL_BONUS_OBJ = $(GNL_BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

bonus: $(OBJ) $(B_OBJ) $(GNL_BONUS_OBJ)
	ar rc ${NAME} $(B_OBJ) $(GNL_BONUS_OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(B_OBJ) $(GNL_BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all