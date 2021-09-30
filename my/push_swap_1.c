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
	int				idx; //не нужен
	int				score; //?
}					t_stack;

typedef struct s_global //структура для хранения общих данных
{
	t_stack	*head_a; //корень стека А
	t_stack	*head_b;
	t_stack	*cur_a; //текущий узел
	t_stack	*cur_b; //текущий узел - вроде не нужен
	int		size_a;
	int		size_b;
	int		ttl_size;
	int		max;
	int		min;
	int		mid;
	long	*arr_argv;
	long	*arr_sort;

}			t_global;


long	ft_atoi(const char *s)
{
	int	i;
	long	res;
	int	sign;

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

  p = lst;
  printf("распечатка стека\n");
  do {
    printf("%d ", p->el); // вывод значения элемента p
    p = p->nxt; // переход к следующему узлу
  } while (p != NULL); // условие окончания обхода
}
//

t_stack	*ft_stk_delhead(t_stack *root) //stk_prv указатель на предыдущий узел, т.е. на тот после которого мы вставляем новый узел
{
	t_stack	*newroot; //указатель на след узел stk_prv->next

	newroot = root->nxt;
	newroot->prv = NULL;
	free(root);
	return (newroot); //новый корень списка
}

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

t_stack	*ft_stk_add_el(t_stack *stk_cur, int data) //stk_cur указатель на текущий узел, т.е. на тот после которого мы вставляем новый узел и он станет предыдущим prv
{
	t_stack	*new; //указатель на новый узел
	t_stack	*stk_nxt; //указатель на след узел stk_cur->next
	//stk_cur - указатель на текущий узел


	stk_nxt = stk_cur->nxt;
	new = (t_stack *)malloc(sizeof(t_stack));
	stk_cur->nxt = new;
	new->el = data;
	new->nxt = stk_nxt;
	new->prv = stk_cur;
	if (stk_nxt != NULL)
		stk_nxt->prv = new;
	return (new);
}


t_stack	*ft_stk_init(int data) //(s_stack_a	*prev, t_stack_a *next, int el, int	idx, int size) здесь буду записывать значения из argv в стек А
{
	t_stack	*stk0;

	stk0 = (t_stack *)malloc(sizeof(t_stack));
	printf("stk0 = %p\n", stk0);
	stk0->el = data;
	printf("stk0-el = %d\n", stk0->el);
	stk0->nxt = NULL;
	printf("stk0-nxt = %p\n", stk0->nxt);
	stk0->prv = NULL;
	printf("stk0-prv = %p\n", stk0->prv);
	return (stk0); //указатель на корень списка
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


t_global	ft_argv_to_array(t_global glb, char **argv) //1.3 Поместить в другой массив для анализа? или в список
{
	int		i;

	glb.arr_argv = (long *)malloc(sizeof(long) * glb.ttl_size);
	glb.arr_sort = (long *)malloc(sizeof(long) * glb.ttl_size);
	i = 0;
	while (i < glb.ttl_size)
	{
		glb.arr_argv[i] = ft_atoi(argv[i + 1]);
		glb.arr_sort[i] = glb.arr_argv[i];
		i++;
	}

	//Находим max, min, mid и сортировка массива для анализа и валидации
	ft_sort_arr(glb.arr_sort, glb.ttl_size);
	glb.min = glb.arr_sort[0];
	glb.max = glb.arr_sort[glb.ttl_size - 1];
	glb.mid = glb.arr_sort[glb.ttl_size/2];

	//распечатка sorted array > УДАЛИТЬ
	printf("Отсортированный массив \n");
	i = 0;
	while(i < glb.ttl_size)
	{
		printf("%ld ", glb.arr_sort[i]);
		i++;
	}
	printf("\n");
	//

	return (glb);
}

/* ОПЕРАЦИИ СО СТЕКОМ */

void	ft_stk_push_el(t_stack *head_from, t_stack *head_to) //stk_cur указатель на текущий узел, т.е. на тот после которого мы вставляем новый узел и он станет предыдущим prv
{
	t_stack	*tmp;

	tmp = head_to;
	head_to = head_from;
	head_from = head_from->nxt;
	head_from->prv = NULL;
	head_to->nxt = tmp;
	tmp->prv = head_to;
}

t_global	ft_pb(t_global glb)
{
	if (glb.head_a->el != glb.min && glb.head_a->el != glb.max)
	{
		write(1, "start pb\n", 9);
		ft_stk_push_el(&glb.head_a, &glb.head_b);
		glb.size_a--;
		glb.size_b++;
		write(1, "pb\n", 3);
	}
	return (glb);
}

t_global ft_stack_sort(t_global glb)
{
	t_stack	*tmp;

	//если ttl_size < 4 то делать pb не имеет смысла
	//pb всех эл-в из А в B, кроме max и min
	glb.size_b = 0;
	glb.head_b = NULL;
	tmp = glb.head_a;
	glb = ft_pb(glb);
	while (tmp->nxt != NULL)
	{
		tmp = tmp->nxt;
		glb = ft_pb(glb);
	}


	return (glb);
}
/**/

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	long	*args, *arr_sort; //массив в котором числа полученные из строки аргументов и отсортированный массив
	t_global	glb; //хранит указатели на корни списков и текущие узлы, и общие данные

	if (argc < 3)
		return (-1); // добавить - если argc = 2 то прогнать argv[1] через split на случай если подали аргументы в кавычках "1 3 6 2 4" и отправить на проверку валидности

	glb.ttl_size = argc - 1;
	//1.3 Поместить в другой массив для анализа? или в список
	glb = ft_argv_to_array(glb, argv);

	//распечатка введенных значений > УДАЛИТЬ
	i = 0;
	while(i < glb.ttl_size)
	{
		printf("массив %ld\n", glb.arr_argv[i]);
		i++;
	}
	//
	printf("Начало инициализации стека\n");
	glb.head_a = ft_stk_init(glb.arr_argv[0]); //инициализация стека А создание корневого элемента - узла
	printf("инициализация стека ОК\n");

	// копирование эл-в в стек А
	glb.cur_a = glb.head_a;
	i = 1;
	while (i < glb.ttl_size)
	{
		glb.cur_a  = ft_stk_add_el(glb.cur_a, glb.arr_argv[i]); //копирование элементов из массива в стек А
		i++;
	}




	printf("копирование эл-в в стек А ОК\n");
	listprint(glb.head_a); //распечатка элементов списка (стека А) - УДАЛИТЬ
	printf("Конец распечатки стека\n");
	//функция работы со стеками
	glb = ft_stack_sort(glb);

	return (0);
}
