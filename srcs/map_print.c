/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:15:56 by tgreil            #+#    #+#             */
/*   Updated: 2018/05/16 12:08:10 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		map_print_more(t_lem_in *cont)
{
	t_room	*tmp;
	int		i;

	tmp = cont->rooms;
	while (tmp)
	{
		i = 0;
		if (tmp->is_valid)
		{
			while (i < tmp->linked)
			{
				if (tmp->branch[i]->is_valid && tmp->branch[i]->turn == -2)
					ft_printf("%s-%s\n", tmp->name, tmp->branch[i]->name);
				i++;
			}
		}
		tmp->turn = -1;
		tmp = tmp->next;
	}
}

void		map_print(t_lem_in *cont)
{
	t_room	*tmp;

	ft_printf("%d\n", cont->nbr);
	ft_printf("##start\n%s %d %d\n", cont->start->name,
											cont->start->x, cont->start->y);
	ft_printf("##end\n%s %d %d\n", cont->end->name,
												cont->end->x, cont->end->y);
	tmp = cont->rooms;
	while (tmp)
	{
		if (tmp != cont->start && tmp != cont->end && tmp->is_valid)
			ft_printf("%s %d %d\n", tmp->name, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	map_print_more(cont);
	ft_printf("\n");
	cont += 1;
}
