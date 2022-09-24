/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/10 19:08:14 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_arr(long *mass, int n)
{
	int		i;
	int		j;
	long	tmp;
	long	min_pos;

	i = 0;
	while (i < n)
	{
		min_pos = i;
		j = i + 1;
		while (j < n)
		{
			if (mass[min_pos] > mass[j])
				min_pos = j;
			j++;
		}
		tmp = mass[min_pos];
		mass[min_pos] = mass[i];
		mass[i] = tmp;
		i++;
	}
}

long	ft_atoi(const char *s, t_global *glb)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	sign = 1;
	while (s[i] && ((s[i] == 32) || ((s[i] > 8) && (s[i] < 14))))
		i++;
	if (s[i] == 45)
	{
		sign = -1;
		i++;
	}
	else
		if (s[i] == 43)
			i++;
	if (s[i] == '\0' || s[i] == 32 || ((s[i] > 8) && (s[i] < 14)))
		ft_exit (2, glb);
	res = 0;
	while ((s[i] > 47) && (s[i] < 58))
		res = (s[i++] - 48) + res * 10;
	if (s[i] != '\0' && s[i] != 32 && ((s[i] < 9) || (s[i] > 13)))
		ft_exit (2, glb);
	return (res * sign);
}

void	ft_check(t_global *glb)
{
	int	i;
	int	sorted;

	i = 0;
	sorted = 1;
	while (i < glb->ttl_size)
	{
		if (glb->arr_argv[i] != glb->arr_sort[i])
			sorted = 0;
		if (i + 1 < glb->ttl_size)
			if (glb->arr_sort[i] == glb->arr_sort[i + 1])
				ft_exit(2, glb);
		i++;
	}
	if (glb->max > INT_MAX || glb->min < INT_MIN)
		ft_exit(2, glb);
	if (glb->prn_flag == 1)
		if (sorted == 1)
			ft_exit(0, glb);
}

void	ft_argv_to_array(t_global *glb, char **argv)
{
	int		i;

	glb->arr_argv = (long *)malloc(sizeof(long) * glb->ttl_size);
	glb->arr_sort = (long *)malloc(sizeof(long) * glb->ttl_size);
	if (glb->arr_argv == NULL || glb->arr_sort == NULL)
		ft_exit(5, glb);
	i = 0;
	while (i < glb->ttl_size)
	{
		glb->arr_argv[i] = ft_atoi(argv[i + 1], glb);
		glb->arr_sort[i] = glb->arr_argv[i];
		i++;
	}
	ft_sort_arr(glb->arr_sort, glb->ttl_size);
	glb->min = glb->arr_sort[0];
	glb->max = glb->arr_sort[glb->ttl_size - 1];
	glb->mid = glb->arr_sort[glb->ttl_size / 2];
	ft_check(glb);
}
