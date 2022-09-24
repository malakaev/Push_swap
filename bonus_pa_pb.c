/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pa_pb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/11 21:02:16 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ftb_for_pb(t_global *glb)
{
	if (glb->size_a > 1)
	{
		glb->head_a = glb->head_a->nxt;
		glb->head_a->prv = glb->tail_a;
		glb->tail_a->nxt = glb->head_a;
	}
	else
	{
		glb->head_a = NULL;
		glb->tail_a = NULL;
	}
}

void	ftb_pb(t_global *glb)
{
	t_stack	*tmp;

	if (glb->size_a < 1)
		return ;
	tmp = glb->head_a;
	ftb_for_pb(glb);
	if (glb->size_b == 0)
	{
		glb->head_b = tmp;
		glb->tail_b = tmp;
	}
	else
	{
		tmp->nxt = glb->head_b;
		glb->head_b->prv = tmp;
		tmp->prv = glb->tail_b;
		glb->tail_b->nxt = tmp;
		glb->head_b = tmp;
	}
	(glb->size_a)--;
	(glb->size_b)++;
}

void	ftb_pa(t_global *glb)
{
	t_stack	*tmp;

	if (glb->size_b < 1)
		return ;
	tmp = glb->head_b;
	glb->head_b = glb->head_b->nxt;
	glb->head_b->prv = glb->tail_b;
	glb->tail_b->nxt = glb->head_b;
	if (glb->size_a == 0)
	{
		tmp->nxt = tmp;
		tmp->prv = tmp;
		glb->head_a = tmp;
		glb->tail_a = tmp;
	}
	else
	{
		tmp->nxt = glb->head_a;
		glb->head_a->prv = tmp;
		tmp->prv = glb->tail_a;
		glb->tail_a->nxt = tmp;
		glb->head_a = tmp;
	}
	(glb->size_a)++;
	(glb->size_b)--;
}
