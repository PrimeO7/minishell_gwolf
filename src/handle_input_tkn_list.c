/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_tkn_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:49:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 17:16:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_handle_input.h"


/**
 * @brief Iterate to last node of given list.
 *
 * @param lst 			List to be iterated through.
 * @return t_tkn_list* 	Last node of list or NULL if empty.
 */
t_tkn_list	*ft_last(t_tkn_list *lst)
{
	t_tkn_list	*last;

	last = lst;
	while (last)
	{
		if (last -> next == NULL)
			return (last);
		last = last -> next;
	}
	return (NULL);
}

/**
 * @brief Create a new node and add it to the end of the token list.
 *
 * @param lst_head	Head node of token list.
 * @param content	Content string to be written into new node.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_new_node(t_tkn_list	**lst_head, char *content)
{
	t_tkn_list	*new;

	new = malloc(sizeof(t_tkn_list));
	if (!new)
		return (ERR_MALLOC);
	new->content = content;
	new->next = NULL;
	ft_add_lst(lst_head, new);
	return (SUCCESS);
}

/**
 * @brief Go to end of token list and connect given token.
 *
 * If there is a (last) node in the list, connect new token to the end.
 * If the list is yet empty, set new token as head of the list.
 * @param lst Token list.
 * @param new Given token to be added to token list.
 */
void	ft_add_lst(t_tkn_list **lst, t_tkn_list *new)
{
	t_tkn_list	*tmp;

	tmp = ft_last(*lst);
	if (tmp)
	{
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*lst = new;
		new->prev = NULL;
	}
}

t_err	ft_new_node_mid(t_tkn_list **lst_head, char *content)
{
	t_tkn_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (ERR_MALLOC);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	ft_add_lst_mid(*lst_head, new);
	(*lst_head) = (*lst_head)->next;
	return (SUCCESS);
}

void	ft_add_lst_mid(t_tkn_list *cur, t_tkn_list *new)
{
	new->next = cur->next;
	if (cur->next)
		cur->next->prev = new;
	cur->next = new;
	new->prev = cur;
}
