/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 11:45:48 by tgreil            #+#    #+#             */
/*   Updated: 2018/05/26 16:35:13 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			parse_nbr(t_lem_in *container, char **line)
{
	while (parse_get_type(*line) == TYPE_COMMENT)
	{
		free(*line);
		get_next_line(0, line);
	}
	container->nbr = ft_atoi(*line);
	if (container->nbr <= 0)
		return (E_ERROR + ft_puterror());
	return (E_SUCCESS);
}

int			parse_room(t_lem_in *container, char *line)
{
	t_coord	coord;
	char	*name;
	int		i;

	i = 0;
	if (line && *line == 'L')
		return (E_ERROR);
	while (line[i] && line[i] != ' ')
		i++;
	if (!i || line[i] != ' ' || !(name = ft_strndup(line, i++)))
		return (E_ERROR);
	coord.x = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i++] != ' ' || coord.x < 0 || (coord.y = ft_atoi(line + i)) < 0)
		return (E_ERROR);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] != '\0')
		return (E_ERROR);
	return (room_add(container, name, &coord));
}

int			parse_pipe(t_lem_in *container, char *line)
{
	t_room	*one;
	t_room	*two;
	int		i;

	i = 0;
	one = container->rooms;
	while (line[i] && line[i] != '-')
		i++;
	while (one && ft_strncmp(one->name, line, i))
		one = one->next;
	if (!one)
		return (E_ERROR);
	two = container->rooms;
	while (two && ft_strcmp(two->name, line + i + 1))
		two = two->next;
	if (!two || one == two)
		return (E_ERROR);
	i = 0;
	while (i < one->linked)
	{
		if (one->branch[i] == two)
			return (E_ERROR);
		i++;
	}
	return (rooms_link(one, two, 0));
}

int			parse_instruction(t_lem_in *container, char *line)
{
	if (!ft_strcmp(line, "##start"))
		container->instruction = INSTRUCTION_START;
	else if (!ft_strcmp(line, "##end"))
		container->instruction = INSTRUCTION_END;
	else
		container->instruction = NO_INSTRUCTION;
	return (E_SUCCESS);
}

int			parse_comment(t_lem_in *container, char *line)
{
	container += 1;
	line += 1;
	return (E_SUCCESS);
}
