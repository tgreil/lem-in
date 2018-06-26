/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:45:47 by tgreil            #+#    #+#             */
/*   Updated: 2018/05/26 16:31:58 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				parse_get_type(char *line)
{
	if (line[0] == '#' && line[1] == '#')
		return (TYPE_INSTRUCTION);
	if (line[0] == '#')
		return (TYPE_COMMENT);
	while (*line)
	{
		if (*line == '-')
			return (TYPE_PIPE);
		line++;
	}
	return (TYPE_ROOM);
}

int				freeer(t_lem_in *container)
{
	t_room		*last;
	t_room		*act;

	act = container->rooms;
	while (act)
	{
		last = act;
		act = act->next;
		free(last->branch);
		free(last->name);
		free(last);
	}
	return (E_SUCCESS);
}

void			lem_init(t_lem_in *container, char *line, int ac, char **av)
{
	if (ac > 1 && !ft_strcmp(av[1], "--color"))
		container->to_color = TRUE;
	else
		container->to_color = FALSE;
	free(line);
	container->rooms = NULL;
	container->instruction = NO_INSTRUCTION;
	container->start = NULL;
	container->end = NULL;
	container->nbr_in = 0;
	container->nbr_out = 0;
}

int				main(int ac, char **av)
{
	t_lem_in	container;
	int			type;
	char		*line;

	if (get_next_line(0, &line) <= 0 || parse_nbr(&container, &line) == E_ERROR)
		return (E_ERROR);
	lem_init(&container, line, ac, av);
	while (get_next_line(0, &line) > 0)
	{
		type = parse_get_type(line);
		if (type == TYPE_ROOM)
			type = parse_room(&container, line);
		else if (type == TYPE_PIPE)
			type = parse_pipe(&container, line);
		else if (type == TYPE_INSTRUCTION)
			type = parse_instruction(&container, line);
		else
			type = parse_comment(&container, line);
		if (type == E_ERROR)
			break ;
		free(line);
	}
	lem_in(&container);
	return (freeer(&container));
}
