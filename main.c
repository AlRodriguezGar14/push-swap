/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:38:47 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/28 16:30:27 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_value(int nbr, int *arr, int max_len)
{
	int	idx;

	idx = 0;
	while (idx < max_len)
	{
		if (arr[idx] == nbr)
			return (idx);
		idx++;
	}
	return (idx);
}

void	assign_idx(t_dll **stack, int *arr)
{
	int		idx;
	t_node	*curr;

	idx = 0;
	curr = (*stack)->head;
	while (idx < (*stack)->len)
	{
		curr->final_idx = find_value(curr->value, arr, (*stack)->len);
		curr = curr->next;
		idx++;
	}
}

static void	free_all(int *arr, t_dll **a, t_dll **b)
{
	if (arr)
		free(arr);
	if (*b != NULL)
		free_dll(b);
	if (*a != NULL)
		free_dll(a);
}

int	main(int argc, char **argv)
{
	t_dll	*stack_a;
	t_dll	*stack_b;
	int		*sorted_arr;

	sorted_arr = NULL;
	while (1)
	{
		stack_b = new_dll();
		stack_a = parse_input(argc, argv);
		if (!stack_a || is_sorted(stack_a))
			break ;
		sorted_arr = sort_input(*stack_a);
		if (!sorted_arr)
			break ;
		assign_idx(&stack_a, sorted_arr);
		if (stack_a->len == 3)
			sort_three(&stack_a);
		if (stack_a->len == 5)
			sort_five(&stack_a, &stack_b);
		while (!is_sorted(stack_a))
			radix_sort(&stack_a, &stack_b);
		break ;
	}
	return (free_all(sorted_arr, &stack_a, &stack_b), 0);
}
