/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/09 20:37:23 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_final(t_global *glb)
{
	int		i;
	t_stack	*tmp;

	i = 0;
	tmp = glb->head_a;
	while (tmp->el != glb->min)
	{
		tmp = tmp->nxt;
		i++;
	}
	if (i > (glb->size_a - i))
		while (glb->head_a->el != glb->min)
			ft_rra(glb);
	else
		while (glb->head_a->el != glb->min)
			ft_ra(glb);
}

void	ft_predsort_a(t_global *glb)
{
	t_stack	*tmp;

	tmp = glb->head_a;
	while (tmp->el != glb->max)
		tmp = tmp->nxt;
	if (tmp->nxt->el == glb->mid)
		ft_sa(glb);
}

void	ft_sort_push_var03(t_global *glb)
{
	if (glb->to_push->var == 0)
	{
		while (glb->head_b != glb->to_push && glb->head_a != glb->place)
			ft_rr(glb);
		while (glb->head_b != glb->to_push)
			ft_rb(glb);
		while (glb->head_a != glb->place)
			ft_ra(glb);
	}
	if (glb->to_push->var == 3)
	{
		while (glb->head_b != glb->to_push && glb->head_a != glb->place)
			ft_rrr(glb);
		while (glb->head_b != glb->to_push)
			ft_rrb(glb);
		while (glb->head_a != glb->place)
			ft_rra(glb);
	}
}

void	ft_sort_push(t_global *glb)
{
	if (glb->to_push->var == 0)
		ft_sort_push_var03(glb);
	if (glb->to_push->var == 1)
	{
		while (glb->head_b != glb->to_push)
			ft_rb(glb);
		while (glb->head_a != glb->place)
			ft_rra(glb);
	}
	if (glb->to_push->var == 2)
	{
		while (glb->head_b != glb->to_push)
			ft_rrb(glb);
		while (glb->head_a != glb->place)
			ft_ra(glb);
	}
	if (glb->to_push->var == 3)
		ft_sort_push_var03(glb);
	ft_pa(glb);
}

void	ft_stack_sort(t_global *glb)
{
	while (glb->size_a > 3)
	{
		if (glb->head_a->el != glb->min && glb->head_a->el != glb->max && \
			glb->head_a->el != glb->mid)
		{
			if (glb->head_a->el < glb->mid && glb->flag == 1)
			{
				ft_pb(glb);
				ft_rb(glb);
			}
			else
			{
				ft_pb(glb);
				glb->flag = 1;
			}
		}
		else
			ft_ra(glb);
	}
	ft_predsort_a(glb);
	while (glb->size_b > 0)
	{
		ft_scoring_main(glb);
		ft_sort_push(glb);
	}
}
