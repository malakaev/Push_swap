/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:01:24 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/11 21:09:28 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

void	ftb_check_sort_stack(t_global *glb)
{
	t_stack	*tmp;

	tmp = glb->head_a;
	while (tmp != glb->tail_a)
	{
		if (tmp->el > tmp->nxt->el)
			ft_exit_ok(4, glb);
		tmp = tmp->nxt;
	}
	if (glb->size_b == 0)
		ft_exit_ok(0, glb);
	ft_exit_ok(4, glb);
}

void	ftb_compare(char *line, t_global *glb, size_t len)
{
	if (!ft_strncmp(line, "sa", len) && len == 2)
		ftb_sa(glb);
	else if (!ft_strncmp(line, "sb", len) && len == 2)
		ftb_sb(glb);
	else if (!ft_strncmp(line, "ss", len) && len == 2)
		ftb_ss(glb);
	else if (!ft_strncmp(line, "pa", len) && len == 2)
		ftb_pa(glb);
	else if (!ft_strncmp(line, "pb", len) && len == 2)
		ftb_pb(glb);
	else if (!ft_strncmp(line, "ra", len) && len == 2)
		ft_ra(glb);
	else if (!ft_strncmp(line, "rb", len) && len == 2)
		ft_rb(glb);
	else if (!ft_strncmp(line, "rr", len) && len == 2)
		ft_rr(glb);
	else if (!ft_strncmp(line, "rra", len) && len == 3)
		ft_rra(glb);
	else if (!ft_strncmp(line, "rrb", len) && len == 3)
		ft_rrb(glb);
	else if (!ft_strncmp(line, "rrr", len) && len == 3)
		ft_rrr(glb);
	else
		ft_exit(1, glb);
}

void	ftb_pars_commands(t_global *glb)
{
	char	*line;
	int		gnl;

	line = NULL;
	gnl = get_next_line(0, &line);
	while (gnl > 0)
	{
		ftb_compare(line, glb, ft_strlen(line));
		free(line);
		line = NULL;
		gnl = get_next_line(0, &line);
	}
	if (gnl == 0)
		free(line);
	if (gnl == -1)
		ft_exit(4, glb);
}
