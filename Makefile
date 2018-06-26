# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/07 16:24:07 by tgreil            #+#    #+#              #
#    Updated: 2018/05/15 11:15:04 by tgreil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c			\
			parse.c			\
			room.c			\
			lem_in.c		\
			lem_in_turn.c	\
			ft_puterror.c	\
			map_print.c

OBJS	= $(addprefix srcs/, $(SRCS:.c=.o))

LIBS	= -Llibft/ -lft

PROJECT = lem_in_project

NAME	= lem-in

RM	= rm -f

CC	= gcc

MAKELIB	= make -C libft/

LIB	= libft/libft.a

CFLAGS	= -W -Wall -Wextra -Werror
CFLAGS	+= -Iincludes/ -Ilibft/includes/

LDFLAGS	=  $(LIBS)

$(PROJECT):	$(LIB) $(NAME)

$(NAME): 	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIB):
	$(MAKELIB)

all:	$(PROJECT)

clean:
	$(RM) $(OBJS)
	$(MAKELIB) clean

fclean:
	$(RM) $(OBJS)
	$(MAKELIB) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	re fclean clean all $(PROJECT)
