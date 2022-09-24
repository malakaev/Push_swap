/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_sa_sb_ss.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/11 20:53:10 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ftb_sa(t_global *glb)
{
	t_stack	*tmp;

	if (glb->size_a < 2)
		return ;
	if (glb->size_a == 2)
	{
		tmp = glb->head_a->nxt;
		glb->tail_a = glb->head_a;
		glb->head_a = tmp;
		return ;
	}
	tmp = glb->head_a->nxt;
	tmp->prv = glb->tail_a;
	glb->head_a->prv = tmp;
	glb->head_a->nxt = tmp->nxt;
	tmp->nxt->prv = glb->head_a;
	tmp->nxt = glb->head_a;
	glb->head_a = tmp;
	glb->tail_a->nxt = glb->head_a;
}

void	ftb_sb(t_global *glb)
{
	t_stack	*tmp;

	if (glb->size_b < 2)
		return ;
	if (glb->size_b == 2)
	{
		tmp = glb->head_b->nxt;
		glb->tail_b = glb->head_b;
		glb->head_b = tmp;
		return ;
	}
	tmp = glb->head_b->nxt;
	tmp->prv = glb->tail_b;
	glb->head_b->prv = tmp;
	glb->head_b->nxt = tmp->nxt;
	tmp->nxt->prv = glb->head_b;
	tmp->nxt = glb->head_b;
	glb->head_b = tmp;
	glb->tail_b->nxt = glb->head_b;
}

void	ftb_ss(t_global *glb)
{
	if (glb->size_a > 1)
		ftb_sa(glb);
	if (glb->size_b > 1)
		ftb_sb(glb);
}
