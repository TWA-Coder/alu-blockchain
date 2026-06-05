CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -I.
AR = ar
ARFLAGS = rcs

SRC = sha256.c ec_create.c ec_to_pub.c ec_from_pub.c ec_save.c ec_load.c ec_sign.c ec_verify.c
OBJ = $(SRC:.c=.o)
LIB = libhblk_crypto.a

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

clean:
	$(RM) *~ $(OBJ) $(LIB)
