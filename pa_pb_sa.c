/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_pb_sa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/10 20:22:48 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sa(t_global *glb)
{
	t_stack	*tmp;

	if (glb->size_a < 2)
		return ;
	tmp = glb->head_a->nxt;
	tmp->prv = glb->tail_a;
	glb->head_a->prv = tmp;
	glb->head_a->nxt = tmp->nxt;
	tmp->nxt->prv = glb->head_a;
	tmp->nxt = glb->head_a;
	glb->head_a = tmp;
	glb->tail_a->nxt = glb->head_a;
	if (glb->prn_flag == 1)
		write(1, "sa\n", 3);
}

void	ft_pb(t_global *glb)
{
	t_stack	*tmp;

	tmp = glb->head_a;
	glb->head_a = glb->head_a->nxt;
	glb->head_a->prv = glb->tail_a;
	glb->tail_a->nxt = glb->head_a;
	if (glb->size_b == 0)
	{
		tmp->nxt = tmp;
		tmp->prv = tmp;
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
	if (glb->prn_flag == 1)
		write(1, "pb\n", 3);
}

void	ft_pa(t_global *glb)
{
	t_stack	*tmp;

	tmp = glb->head_b;
	if (glb->size_b > 1)
	{
		glb->head_b = glb->head_b->nxt;
		glb->head_b->prv = glb->tail_b;
		glb->tail_b->nxt = glb->head_b;
	}
	else
	{
		glb->head_b = NULL;
		glb->tail_b = NULL;
	}
	tmp->nxt = glb->head_a;
	glb->head_a->prv = tmp;
	tmp->prv = glb->tail_a;
	glb->tail_a->nxt = tmp;
	glb->head_a = tmp;
	(glb->size_a)++;
	(glb->size_b)--;
	if (glb->prn_flag == 1)
		write(1, "pa\n", 3);
}
