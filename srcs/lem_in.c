/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 14:32:57 by tgreil            #+#    #+#             */
/*   Updated: 2018/05/16 12:04:27 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			lem_init_distance(t_room *room, int distance)
{
	int		i;

	i = 0;
	room->occuped = 0;
	room->turn = -2;
	room->is_valid = TRUE;
	if (room->distance == -1 || room->distance > distance)
		room->distance = distance;
	else
		return (E_SUCCESS);
	while (i < room->linked)
	{
		lem_init_distance(room->branch[i], distance + 1);
		i++;
	}
	return (E_SUCCESS);
}

int			lem_in_remove(t_lem_in *cont, t_room *room, int flag)
{
	int		room_valid;
	int		i;

	i = 0;
	if (!room)
		return (E_SUCCESS);
	room_valid = 0;
	while (i < room->linked)
	{
		if (room->branch[i]->is_valid == TRUE)
			room_valid++;
		i++;
	}
	if (room_valid < 2 && room != cont->start && room != cont->end)
		room->is_valid = FALSE;
	else
		room->is_valid = TRUE;
	if (flag)
		return (E_SUCCESS);
	return (lem_in_remove(cont, room->next, 0));
}

int			lem_in_sort_branch(t_room *room)
{
	t_room	*tmp;
	int		i;

	i = 0;
	if (!room)
		return (E_SUCCESS);
	while (i < room->linked)
	{
		if (i && room->branch[i - 1]->distance > room->branch[i]->distance)
		{
			tmp = room->branch[i - 1];
			room->branch[i - 1] = room->branch[i];
			room->branch[i] = tmp;
			i = 0;
		}
		i++;
	}
	return (lem_in_sort_branch(room->next));
}

int			lem_in(t_lem_in *container)
{
	container->turn = 0;
	if (!container->start || !container->end)
		return (E_ERROR + ft_puterror());
	lem_init_distance(container->end, 0);
	if (container->start->distance == -1)
		return (E_ERROR + ft_puterror());
	lem_in_remove(container, container->rooms, 0);
	lem_in_remove(container, container->rooms, 0);
	lem_in_remove(container, container->rooms, 0);
	lem_in_sort_branch(container->rooms);
	map_print(container);
	while (container->nbr_out != container->nbr)
	{
		container->moved = 0;
		lem_in_one_turn(container);
		ft_printf("\n");
		container->turn++;
	}
	return (E_SUCCESS);
}
