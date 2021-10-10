/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:01:24 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/10 20:20:53 by kgolda           ###   ########.fr       */
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
			ft_exit_OK(4, glb);
		tmp = tmp->nxt;
	}
	if (glb->size_b == 0)
		ft_exit_OK(0, glb);
	ft_exit_OK(4, glb);
}

void	ftb_compare(char *line, t_global *glb, size_t len)
{
	// int	len;
	// printf("len = %zu %s\n", len, line);
	// len = ft_strlen(line);
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
		ft_exit(1, glb); //free line?

}

void	ftb_pars_commands(t_global *glb)
{
	char	*line;
	int		gnl;

	line = NULL;
	gnl = get_next_line(0, &line);
	while (gnl > 0)		//correct input
	{
		//res = get_next_line(fd, &line);
		// printf("gnl = %d %s", gnl, line);
		// printf("\n");
		ftb_compare(line, glb, ft_strlen(line)); //сравниваем получ-ю строку с командами sa, sb, ss, ra, rb, rr, rra, rrb, rrr
		free(line);
		line = NULL;
		gnl = get_next_line(0, &line);
	}
	if (gnl == 0)
	{
		// printf("gnl = %d\n", gnl);
		// printf("line =%s\n", line);
		// printf("%d", *line);
		free(line);
	}
	if (gnl == -1)
		ft_exit(4, glb);
}
