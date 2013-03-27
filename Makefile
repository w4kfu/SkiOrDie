CC 		= gcc
RM      	= rm -f
CFLAGS 		= -W -Wall -Wextra -ansi -pedantic -D_BSD_SOURCE -std=c99

SRC_DIR 	= src
SRC_C		= 	$(SRC_DIR)/main.c	\
			$(SRC_DIR)/arg.c	\
			$(SRC_DIR)/uncomp.c	
NAME 		= skiordietoolz
OBJ 		= $(SRC_C:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

distclean:  clean
	$(RM) -rf $(NAME)

.PHONY:  clean all distclean
