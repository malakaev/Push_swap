/* 	ПЛАН
	1. 	1.1) Парсинг чисел поданных в argv
			- если argc = 2 то прогнать argv[1] через split
		1.2) Проверка элементов на валидность, если не int и если повторяются то ошибка
		1.3) ? Поместить в другой массив для анализа?

	2.	2.1) Создать стеки (односвязный список, двусвязный список, массив?) OK
		2.2) Поместить элементы в стек А = ОК
		2.3) Написать функции работы со стеком (sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr)
			-
	3.	3.1) Алгоритмы сортировки
		3.2) Анализ элементов для выбора алгоритма сортировки

	4.	Makefile который компилирует программу в push_swap
*/

#include <stdio.h> //for printf
#include <unistd.h> //for write, read (ssize_t read(int fildes, void *buf, size_t nbyte);)
#include <stdlib.h> //for malloc, free
#include <fcntl.h> //for open
//#include "push_swap.h"

typedef struct s_stack
{
	struct s_stack	*prv;
	struct s_stack	*nxt;
	int				el;
	int				score;
	int				var;
}					t_stack;

typedef struct s_global //структура для хранения общих данных
{
	t_stack	*head_a; //корень стека А
	t_stack	*head_b;
	t_stack	*cur_a; //текущий узел
	t_stack	*cur_b; //текущий узел - вроде не нужен
	t_stack	*tail_a; //конец стека А
	t_stack	*tail_b;
	int		size_a;
	int		size_b;
	int		ttl_size;
	int		max;
	int		min;
	int		mid;
	long	*arr_argv; //массив значений полученный из аргументов (из argv)
	long	*arr_sort; //отсортированный массив значений

}			t_global;

typedef struct s_score
{
	int				a1;
	int				a2;
	int				b1;
	int				b2;
}					t_score;


long	ft_atoi(const char *s)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	sign = 1;
	while (s[i] && ((s[i] == 32) || ((s[i] > 8) && (s[i] < 14)))) //пропуск разных пробелов
		i++;
	if (s[i] == 45) //если есть минус
	{
		sign = -1;
		i++;
	}
	else
		if (s[i] == 43) //если есть +
			i++;
	res = 0;
	while ((s[i] > 47) && (s[i] < 58))
		res = (s[i++] - 48) + res * 10;
	return (res * sign);
}

//Проверка валидности арг-в
/*
int	ft_valid(char *s, int argc)
{
	int	i;
	int	ar[argc];

	i = 0;
	while (i < argc)
	{
		ar[i] = ft_atoi(s[i]);

	}
}*/

//УДАЛИТЬ! только для проверки
void listprint(t_stack *lst)
{
  t_stack *p;

	if (lst == NULL)
		return ;
  p = lst;
  printf("\nраспечатка стека\n");
  printf("elm ");
  do {
    printf("%d ", p->el); // вывод значения элемента p
    p = p->nxt; // переход к следующему узлу
  } while (p != lst); // условие окончания обхода
    printf("\nscr ");
    p = lst;
  do {
    printf("%d ", p->score); // вывод значения элемента p
    p = p->nxt; // переход к следующему узлу
  } while (p != lst); // условие окончания обхода
   printf("\nvar ");
    p = lst;
  do {
    printf("%d ", p->var); // вывод значения элемента p
    p = p->nxt; // переход к следующему узлу
  } while (p != lst); // условие окончания обхода
  printf("\n ");
}
//

/* //вроде не нужно
t_stack	*ft_stk_delhead(t_stack *root) //stk_prv указатель на предыдущий узел, т.е. на тот после которого мы вставляем новый узел
{
	t_stack	*newroot; //указатель на след узел stk_prv->next

	newroot = root->nxt;
	newroot->prv = NULL;
	free(root);
	return (newroot); //новый корень списка
}

//вроде не нужно
t_stack	*ft_stk_del_el(t_stack *current) //stk_prv указатель на предыдущий узел, т.е. на тот после которого мы вставляем новый узел
{
	t_stack	*prev; //указатель на новый узел
	t_stack	*next; //указатель на след узел stk_prv->next

	next = current->nxt;
	prev = current->prv;
	if (next != NULL)
		prev->nxt = next;
	if (prev != NULL)
		next->prv = prev;
	free(current);
	//new->size = argc - 1; //общее кол-во элементов которое будет в списке-стеке А
	return (prev);
}
*/

t_stack	*ft_stk_add_el(t_stack *stk_cur, int data, t_global *glb) //stk_cur указатель на текущий узел, т.е. на тот после которого мы вставляем новый узел и он станет предыдущим prv
{
	t_stack	*new; //указатель на новый узел
	t_stack	*tmp_nxt; //указатель на след узел stk_cur->next
	//stk_cur - указатель на текущий узел


	tmp_nxt = stk_cur->nxt;
	new = (t_stack *)malloc(sizeof(t_stack));
	stk_cur->nxt = new;
	new->el = data;
	new->nxt = tmp_nxt;
	new->prv = stk_cur;
	//if (tmp_nxt != NULL)
		//tmp_nxt->prv = new;
	//else
		glb->tail_a = new;
		glb->head_a->prv = new;
	return (new);
}


t_stack	*ft_stk_init(int data) //(s_stack_a	*prev, t_stack_a *next, int el, int	idx, int size) здесь буду записывать значения из argv в стек А
{
	t_stack	*stk_init;

	stk_init = (t_stack *)malloc(sizeof(t_stack));
	stk_init->el = data;
	stk_init->nxt = stk_init;
	stk_init->prv = stk_init;
	return (stk_init); //указатель на корень списка
}

void	ft_sort_arr(long *mass, int n)
{
	int	i;
	int	j;
	int	tmp;
	int	min_pos;
	long	*arr_sort;

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


void	ft_argv_to_array(t_global *glb, char **argv) //1.3 Поместить в другой массив для анализа? или в список
{
	int		i;

	glb->arr_argv = (long *)malloc(sizeof(long) * glb->ttl_size);
	glb->arr_sort = (long *)malloc(sizeof(long) * glb->ttl_size);
	i = 0;
	while (i < glb->ttl_size)
	{
		glb->arr_argv[i] = ft_atoi(argv[i + 1]);
		glb->arr_sort[i] = glb->arr_argv[i];
		i++;
	}

	//Находим max, min, mid и сортировка массива для анализа и валидации
	ft_sort_arr(glb->arr_sort, glb->ttl_size);
	glb->min = glb->arr_sort[0];
	glb->max = glb->arr_sort[glb->ttl_size - 1];
	glb->mid = glb->arr_sort[glb->ttl_size/2];

	/*распечатка sorted array > УДАЛИТЬ
	printf("Отсортированный массив \n");
	i = 0;
	while(i < glb->ttl_size)
	{
		printf("%ld ", glb->arr_sort[i]);
		i++;
	}
	printf("\n");
	printf("min %d\n", glb->min);
	printf("mid %d\n", glb->mid);
	printf("max %d\n", glb->max);

	*/

}

/* ОПЕРАЦИИ СО СТЕКОМ */

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
		//glb->head_b->prv = NULL;
		//glb->head_b->nxt = NULL;
	}
	tmp->nxt = glb->head_a;
	glb->head_a->prv = tmp;
	tmp->prv = glb->tail_a;
	glb->tail_a->nxt = tmp;
	glb->head_a = tmp;
	(glb->size_a)++;
	(glb->size_b)--;
	write(1, "pa\n", 3);
}

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

void	ft_rr(t_global *glb)
{
	glb->head_a = glb->head_a->nxt;
	glb->tail_a = glb->tail_a->nxt;
	glb->head_b = glb->head_b->nxt;
	glb->tail_b = glb->tail_b->nxt;
	write(1, "rr\n", 3);
}

void	ft_rrr(t_global *glb)
{
	glb->head_a = glb->head_a->prv;
	glb->tail_a = glb->tail_a->prv;
	glb->head_b = glb->head_b->prv;
	glb->tail_b = glb->tail_b->prv;
	write(1, "rrr\n", 4);
}

void	ft_sort_final(t_global *glb)
{
	int	i;
	t_stack *tmp;

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
//Предсортировка стека А в котором осталось 3 узла
void	ft_predsort_a(t_global *glb)
{
	t_stack	*tmp;

	tmp = glb->head_a;
	while (tmp->el != glb->max)
		tmp = tmp->nxt;
	if (tmp->nxt->el == glb->mid)
		ft_sa(glb);
}

//ПУШ из Б в А
void	ft_sort_push(t_stack *to_push, t_stack *place, t_global *glb)
{

	// printf("\npushing to A to_push->el = %d\n", to_push->el);
	// printf("place->el = %d\n", place->el);
	if (to_push->var == 0)
	{
		while (glb->head_b != to_push && glb->head_a != place)
			ft_rr(glb);
		while (glb->head_b != to_push)
			ft_rb(glb);
		while (glb->head_a != place)
			ft_ra(glb);

	}

	if (to_push->var == 1)
	{
		while (glb->head_b != to_push)
			ft_rb(glb);
		while (glb->head_a != place)
			ft_rra(glb);
	}

	if (to_push->var == 2)
	{
		while (glb->head_b != to_push)
			ft_rrb(glb);
		while (glb->head_a != place)
			ft_ra(glb);
	}

	if (to_push->var == 3)
	{
		while (glb->head_b != to_push && glb->head_a != place)
			ft_rrr(glb);
		while (glb->head_b != to_push)
			ft_rrb(glb);
		while (glb->head_a != place)
			ft_rra(glb);
	}
	ft_pa(glb);

}

//СКОРИНГ эл-в стека B если size_b > 1
void	ft_scoring(t_global *glb)
{
	t_stack	*cur_a;
	t_stack	*cur_b;
	t_stack	*to_push;
	t_stack	*place;
	int		sc_sum[4];
	int		min;
	int		min_score;
	int		i;
	int		j;
	t_score	s;

	cur_b = glb->head_b;
	j = 0;
	//s.b1 = j; //sc_b1 и sc_a1 сколько нужно сделать rotate в стеках a или b,
						//sc_b2 и sc_a2 сколько нужно сделать revers-rotate в стеках a или b
	while (cur_b != glb->head_b || j == 0)
	{
		s.b1 = j;
		s.b2 = glb->size_b - s.b1;
		cur_a = glb->head_a;
		s.a1 = 0;
		while ((cur_a != glb->head_a || s.a1 == 0) && (cur_b->el > cur_a->el || cur_b->el < cur_a->prv->el))//ДОБавить условие если b < a
		{
			s.a1++;
			cur_a = cur_a->nxt;
		}
		s.a2 = glb->size_a - s.a1;

		//итоговый score для элемента
		if (s.b1 > s.a1)
			sc_sum[0] = s.b1;
		else
			sc_sum[0] = s.a1;

		if (s.b2 > s.a2)
			sc_sum[3] = s.b2;
		else
			sc_sum[3] = s.a2;

		sc_sum[1] = s.b1 + s.a2;
		sc_sum[2] = s.b2 + s.a1;

		//TO DEL
		// printf("\n\ncur_b-el = %d, b1 = %d, b2 = %d, a1 = %d, a2 = %d\n", cur_b->el, s.b1, s.b2, s.a1, s.a2);
		// i = -1;
		// while (++i < 4)
		// 	printf("\ni = %d, sc_sum = %d", i, sc_sum[i]);

		//находим минимальный score и вариант для сортировки
		i = 1;
		min = sc_sum[0];
		cur_b->var = 0;
		cur_b->score = min;
		while (i < 4)
		{
			if (min > sc_sum[i])
			{
				min = sc_sum[i];
				cur_b->var = i;
				cur_b->score = min;
			}
			i++;
		}

		//printf("\nsc_b1 = %d\n", s.b1);
		//Если score == 0 то нет смысла дальше делать скоринг
		if (cur_b->score == 0)
		{
			to_push = cur_b;
			place = cur_a;
			break;
		}
		//поиск узла с минимальным score
		if (j == 0)
		{
			min_score = cur_b->score;
			to_push = cur_b;
			place = cur_a;
		}
		if (min_score > cur_b->score)
		{
			min_score = cur_b->score;
			to_push = cur_b;
			place = cur_a;
		}
		cur_b = cur_b->nxt;
		j++;
	}
	//listprint(glb->head_a);
	//listprint(glb->head_b);

	//пуш узла из Б в А
	ft_sort_push(to_push, place, glb);

}

void	ft_stack_sort(t_global *glb)
{
	t_stack	tmp;
	int		flag = 0;

	//если ttl_size < 4 то делать pb не имеет смысла
	//pb всех эл-в из А в B, кроме max и min
	glb->size_b = 0;
	glb->head_b = NULL;

	while (glb->size_a > 3)
		if (glb->head_a->el != glb->min && glb->head_a->el != glb->max && glb->head_a->el != glb->mid)
			if (glb->head_a->el < glb->mid && flag == 1) //&& glb->size_b > 2)
			{
				ft_pb(glb);
				ft_rb(glb);
			}
			else
			{
				ft_pb(glb);
				flag = 1; //условие чтобы rb делать только если эл-т > mid уже попал в стек B
			}
		else
			ft_ra(glb);
	ft_predsort_a(glb);
	//printf("Рез-т перед скорингом\n");
	//listprint(glb->head_a);
	//listprint(glb->head_b);
	//скоринг эл-в стека B
	while (glb->size_b > 0)
		ft_scoring(glb);
	//финальная прокрутка стека А для законченной сортировки
	ft_sort_final(glb);

	//printf("\nПосле скоринга\n");
	//listprint(glb->head_a);
	//listprint(glb->head_b);
}
/**/

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	long	*args, *arr_sort; //массив в котором числа полученные из строки аргументов и отсортированный массив
	t_global	*glb; //хранит указатели на корни списков и текущие узлы, и общие данные

	if (argc < 3)
		return (-1); // добавить - если argc = 2 то прогнать argv[1] через split на случай если подали аргументы в кавычках "1 3 6 2 4" и отправить на проверку валидности

	glb = (t_global *)malloc(sizeof(t_global));
	glb->ttl_size = argc - 1;
	glb->size_a = glb->ttl_size;
	//1.3 Поместить в другой массив для анализа? или в список
	ft_argv_to_array(glb, argv);

	//printf("Начало инициализации стека\n");
	glb->head_a = ft_stk_init(glb->arr_argv[0]); //инициализация стека А создание корневого элемента - узла
	glb->tail_a = glb->head_a; //на случай если 1 арг-т, возможно не нужно
	//printf("инициализация стека ОК\n");

	// копирование эл-в в стек А
	glb->cur_a = glb->head_a;
	i = 1;
	while (i < glb->ttl_size)
	{
		glb->cur_a  = ft_stk_add_el(glb->cur_a, glb->arr_argv[i], glb); //копирование элементов из массива в стек А
		i++;
	}




	// printf("копирование эл-в в стек А ОК\n");
	// listprint(glb->head_a); //распечатка элементов списка (стека А) - УДАЛИТЬ
	// printf("Конец распечатки стека\n");
	//функция работы со стеками
	ft_stack_sort(glb);

	// listprint(glb->head_a);
	// listprint(glb->head_b);

	return (0);
}
