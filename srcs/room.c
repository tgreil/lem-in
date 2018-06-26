/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:13:27 by tgreil            #+#    #+#             */
/*   Updated: 2018/05/03 16:35:15 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			rooms_link(t_room *one, t_room *two, int flag)
{
	t_room	**new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(t_room *) * (one->linked + 1))))
		return (E_ERROR);
	while (i < one->linked)
	{
		new[i] = one->branch[i];
		i++;
	}
	if (one->linked)
		free(one->branch);
	one->branch = new;
	new[i] = two;
	one->linked++;
	if (!flag)
		return (rooms_link(two, one, 1));
	return (E_SUCCESS);
}

int			room_add(t_lem_in *container, char *name, t_coord *c)
{
	t_room	*tmp;
	t_room	*new;

	tmp = container->rooms;
	if (!(new = malloc(sizeof(t_room))))
		return (E_ERROR);
	new->name = name;
	new->linked = 0;
	new->branch = NULL;
	new->distance = -1;
	new->next = NULL;
	new->x = c->x;
	new->y = c->y;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		container->rooms = new;
	else
		tmp->next = new;
	if (container->instruction == INSTRUCTION_START)
		container->start = new;
	else if (container->instruction == INSTRUCTION_END)
		container->end = new;
	container->instruction = NO_INSTRUCTION;
	return (E_SUCCESS);
}
