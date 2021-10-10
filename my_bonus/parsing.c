/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:01:24 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/10 16:28:54 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

ftb_check_sort_stack(glb)
{

}

void	ftb_compare(char *line, t_global *glb, size_t len)
{
	// int	len;

	// len = ft_strlen(line);
	if (!ft_strncmp(line, "sa\n", len) && len == 3)
		ft_sa(glb);
	else if (!ft_strncmp(line, "sb\n", len) && len == 3)
		ft_sb(glb);
	else if (!ft_strncmp(line, "ss\n", len) && len == 3)
		ft_ss(glb);
	else if (!ft_strncmp(line, "pa\n", len) && len == 3)
		ft_pa(glb);
	else if (!ft_strncmp(line, "pb\n", len) && len == 3)
		ft_pb(glb);
	else if (!ft_strncmp(line, "ra\n", len) && len == 3)
		ft_ra(glb);
	else if (!ft_strncmp(line, "rb\n", len) && len == 3)
		ft_rb(glb);
	else if (!ft_strncmp(line, "rr\n", len) && len == 3)
		ft_rr(glb);
	else if (!ft_strncmp(line, "rra\n", len) && len == 4)
		ft_rra(glb);
	else if (!ft_strncmp(line, "rrb\n", len) && len == 4)
		ft_rrb(glb);
	else if (!ft_strncmp(line, "rrr\n", len) && len == 4)
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
		printf("res = %d %s", gnl, line);
		printf("\n");
		ftb_compare(line, glb, ft_strlen(line)); //сравниваем получ-ю строку с командами sa, sb, ss, ra, rb, rr, rra, rrb, rrr
		gnl = get_next_line(0, &line);
		free(line);
	}
	if (gnl == 0)
	{
		printf("fd = %d res = %d\n", fd, res);
		printf("line =%s\n", line);
		// printf("%d", *line);
		//free(line);
	}
	if (gnl == -1)
		printf("err = -1 \n");
	else
	{
		printf("fd = %d res = %d\n", fd, res);
		printf("line =%s\n", line);
		// printf("%d", *line);
		free(line);
	}


}


