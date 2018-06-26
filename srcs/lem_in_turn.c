/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_turn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:41:37 by tgreil            #+#    #+#             */
/*   Updated: 2018/05/15 12:04:15 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		lem_in_print(t_room *to, int nbr, int to_color)
{
	if (to_color == FALSE)
		ft_printf("L%d-%s", nbr, to->name);
	else if (nbr % 5 == 1)
		ft_printf("{*}L%d{eoc}-%s", "light blue", nbr, to->name);
	else if (nbr % 5 == 2)
		ft_printf("{*}L%d{eoc}-%s", "light yellow", nbr, to->name);
	else if (nbr % 5 == 3)
		ft_printf("{*}L%d{eoc}-%s", "light red", nbr, to->name);
	else if (nbr % 5 == 4)
		ft_printf("{*}L%d{eoc}-%s", "light cyan", nbr, to->name);
	else
		ft_printf("{*}L%d{eoc}-%s", "light green", nbr, to->name);
}

int			lem_in_move_one(t_lem_in *cont, t_room *from, t_room *to, int nbr)
{
	if ((to != cont->end && to->occuped) || from->turn == cont->turn ||
		from->from == to || to->is_valid == FALSE)
		return (FALSE);
	if (to != cont->end)
	{
		to->occuped = nbr;
		to->turn = cont->turn;
		to->from = from;
	}
	else
		cont->nbr_out++;
	if (from != cont->start)
	{
		from->from = NULL;
		from->occuped = 0;
	}
	if (cont->moved)
		ft_printf(" ");
	lem_in_print(to, nbr, cont->to_color);
	cont->moved++;
	return (TRUE);
}

int			lem_in_move_in(t_lem_in *cont, t_room *room)
{
	int		i;

	i = 0;
	if (!room)
		return (FALSE);
	while (i < room->linked)
	{
		if (room->occuped && room != cont->end && room != cont->start)
			lem_in_move_one(cont, room, room->branch[i], room->occuped);
		if (room->distance < room->branch[i]->distance)
			lem_in_move_in(cont, room->branch[i]);
		i++;
	}
	return (TRUE);
}

int			lem_in_one_turn(t_lem_in *cont)
{
	int		i;

	i = 0;
	lem_in_move_in(cont, cont->end);
	while (i < cont->start->linked && cont->nbr_in < cont->nbr)
	{
		if (!i || cont->start->branch[i - 1]->distance + cont->nbr -
							cont->nbr_in >= cont->start->branch[i]->distance)
		{
			if (lem_in_move_one(cont, cont->start, cont->start->branch[i],
													cont->nbr_in + 1) == TRUE)
				cont->nbr_in++;
		}
		if (cont->start->branch[0] != cont->end)
			i++;
	}
	return (E_SUCCESS);
}
