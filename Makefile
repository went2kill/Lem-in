# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/08 19:01:12 by yrobotko          #+#    #+#              #
#    Updated: 2017/09/17 21:40:29 by yrobotko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

G = gcc

FLAG = -Wall -Wextra -Werror

SRC =   lemin.c \
		file0.c \
		file1.c \
		file2.c \
		file3.c \
		file4.c \
		file5.c \
		file6.c \
		file7.c \

OBJ = $(SRC:.c=.o)

DEL = rm -f

LIB = libft/libft.a

all: $(NAME)

$(NAME) : $(OBJ)
	make -C ./libft/ re
	gcc $(FLAG) $(LIB) $(OBJ) -o $(NAME) 
%.o: %.c
	$(G) $(CFLAGS) -c -o $@ $<
clean:
	$(DEL) $(OBJ)
	$(DEL) libft/*.o
fclean: clean
	$(DEL) $(NAME)
	$(DEL) libft.a
	$(DEL) lebft/libft.a
re:	fclean
	make

