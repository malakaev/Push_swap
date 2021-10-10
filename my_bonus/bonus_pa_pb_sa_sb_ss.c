/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pa_pb_sa_sb_ss.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/10 20:40:36 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ftb_sa(t_global *glb)
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
	// if (glb->prn_flag == 1)
	// 	write(1, "sa\n", 3);
}

void	ftb_sb(t_global *glb)
{
	t_stack	*tmp;

	if (glb->size_b < 2)
		return ;
	tmp = glb->head_b->nxt;
	tmp->prv = glb->tail_b;
	glb->head_b->prv = tmp;
	glb->head_b->nxt = tmp->nxt;
	tmp->nxt->prv = glb->head_b;
	tmp->nxt = glb->head_b;
	glb->head_b = tmp;
	glb->tail_b->nxt = glb->head_b;
	// if (glb->prn_flag == 1)
		// write(1, "sb\n", 3);
}

void	ftb_ss(t_global *glb)
{
	if (glb->size_b < 2 || glb->size_a < 2)
		return ;
	ftb_sa(glb);
	ftb_sb(glb);
}

void	ftb_pb(t_global *glb)
{
	t_stack	*tmp;
	write(1, "start\n", 6);

	if (glb->size_a < 1)
		return ;
	write(1, "strt2\n", 6);
	tmp = glb->head_a;
	glb->head_a = glb->head_a->nxt;
	glb->head_a->prv = glb->tail_a;
	glb->tail_a->nxt = glb->head_a;
	if (glb->size_b == 0)
	{
		write(1, "strt3\n", 6);
		tmp->nxt = tmp;
		tmp->prv = tmp;
		glb->head_b = tmp;
		glb->tail_b = tmp;
	}
	else
	{
		write(1, "strt4\n", 6);
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
