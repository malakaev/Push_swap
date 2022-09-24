/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_rrr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/12 15:53:23 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rr(t_global *glb)
{
	if (glb->size_a > 1)
	{
		glb->head_a = glb->head_a->nxt;
		glb->tail_a = glb->tail_a->nxt;
	}
	if (glb->size_b > 1)
	{
		glb->head_b = glb->head_b->nxt;
		glb->tail_b = glb->tail_b->nxt;
	}
	if (glb->prn_flag == 1)
		write(1, "rr\n", 3);
}

void	ft_rrr(t_global *glb)
{
	if (glb->size_a > 1)
	{
		glb->head_a = glb->head_a->prv;
		glb->tail_a = glb->tail_a->prv;
	}
	if (glb->size_b > 1)
	{
		glb->head_b = glb->head_b->prv;
		glb->tail_b = glb->tail_b->prv;
	}
	if (glb->prn_flag == 1)
		write(1, "rrr\n", 4);
}
