CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

SRC = sha256.c ec_create.c ec_to_pub.c ec_from_pub.c \
      ec_save.c ec_load.c ec_sign.c ec_verify.c
OBJ = $(SRC:.c=.o)
NAME = libhblk_crypto.a

.PHONY: clean fclean re

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c hblk_crypto.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
