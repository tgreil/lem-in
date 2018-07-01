/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:48:19 by tgreil            #+#    #+#             */
/*   Updated: 2018/07/01 10:18:15 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include "libft.h"

# define TRUE				1
# define FALSE				0
# define E_SUCCESS			0
# define E_ERROR			-1
# define TYPE_COMMENT		1
# define TYPE_INSTRUCTION	2
# define TYPE_ROOM			3
# define TYPE_PIPE			4
# define INSTRUCTION_START	5
# define INSTRUCTION_END	6
# define NO_INSTRUCTION		7
# define ERROR_MSG			"ERROR"

typedef struct				s_coord
{
	int						x;
	int						y;
}							t_coord;

typedef struct				s_room
{
	struct s_room			**branch;
	struct s_room			*next;
	int						linked;
	int						distance;
	char					*name;
	int						x;
	int						y;
	int						occuped;
	struct s_room			*from;
	int						turn;
	int						is_valid;
}							t_room;

typedef struct				s_lem_in
{
	t_room					*rooms;
	t_room					*start;
	t_room					*end;
	int						instruction;
	int						nbr;
	int						nbr_in;
	int						nbr_out;
	int						moved;
	int						turn;
	int						to_color;
}							t_lem_in;

/*
**		main.c
*/
int							parse_get_type(char *line);
int							freeer(t_lem_in *container);
void						lem_init(t_lem_in *con, char *l, int ac, char **av);
int							main(int ac, char **av);

/*
**		lem_in.c
*/
int							lem_init_distance(t_room *room, int distance);
int							lem_in_sort_branch(t_room *room);
int							lem_in(t_lem_in *container);

/*
**		lem_in_turn.c
*/
void						lem_in_print(t_room *to, int nbr, int to_color);
int							lem_in_move_one(t_lem_in *cont, t_room *from,
															t_room *to, int nb);
int							lem_in_move_in(t_lem_in *cont, t_room *room);
int							lem_in_one_turn(t_lem_in *container);

/*
**		parse.c
*/
int							parse_nbr(t_lem_in *container, char **line);
int							parse_room(t_lem_in *container, char *line);
int							parse_pipe(t_lem_in *container, char *line, int i);
int							parse_instruction(t_lem_in *container, char *line);
int							parse_comment(t_lem_in *container, char *line);

/*
**		room.c
*/
int							rooms_link(t_room *one, t_room *two, int flag);
int							room_add(t_lem_in *contain, char *name, t_coord *c);

/*
**		map_print.c
*/
void						map_print_more(t_lem_in *cont);
void						map_print(t_lem_in *container);

/*
**		ft_puterror.c
*/
int							ft_puterror(void);

#endif
