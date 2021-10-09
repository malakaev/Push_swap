/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_rra_rb_rrb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/09 18:30:51 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_ra(t_global *glb)
{
	glb->head_a = glb->head_a->nxt;
	glb->tail_a = glb->tail_a->nxt;
	write(1, "ra\n", 3);
}

void	ft_rra(t_global *glb)
{
	glb->head_a = glb->head_a->prv;
	glb->tail_a = glb->tail_a->prv;
	write(1, "rra\n", 4);
}

void	ft_rb(t_global *glb)
{
	glb->head_b = glb->head_b->nxt;
	glb->tail_b = glb->tail_b->nxt;
	write(1, "rb\n", 3);
}

void	ft_rrb(t_global *glb)
{
	glb->head_b = glb->head_b->prv;
	glb->tail_b = glb->tail_b->prv;
	write(1, "rrb\n", 4);
}
