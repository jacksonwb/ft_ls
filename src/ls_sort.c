/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 19:17:34 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/12 21:40:40 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		lst_cmp(t_list *new, t_list *lst, t_flags flags)
{
	int (*cmp)(t_list *new, t_list *lst);

	if (flags & FLAG_LOWER_T)
		cmp = &t_flag_cmp;
	else
		cmp = &alph_cmp;
	return (flags & FLAG_LOWER_R ? -cmp(new, lst) : cmp(new, lst));
}

void	lst_sort(t_list *new, t_list **head, t_flags flags)
{
	t_list *lst;

	lst = *head;
	if (lst_cmp(new, lst, flags) < 0)
	{
		new->next = lst;
		*head = new;
		return ;
	}
	while (lst)
	{
		if (lst_cmp(new, lst->next, flags) < 0)
		{
			lst_insert_after(new, lst);
			return ;
		}
		if (!lst->next)
		{
			lst->next = new;
			return ;
		}
		lst = lst->next;
	}
}

int		t_flag_cmp(t_list *new, t_list *lst)
{
	int sec;
	int nsec;

	if (lst == NULL)
		return (0);
	if ((sec = get_link_t_sec(lst) - get_link_t_sec(new)))
	{
		return (sec);
	}
	else if ((nsec = get_link_t_nsec(lst) - get_link_t_nsec(new)))
	{
		return (nsec);
	}
	else
		return (alph_cmp(new, lst));
}

void	lst_insert_after(t_list *new, t_list *lst)
{
	t_list *temp;

	temp = lst->next;
	lst->next = new;
	new->next = temp;
}

void	lst_helper(t_list **lst, t_file *content, t_flags flags)
{
	t_list *elem;

	if (!*lst)
	{
		*lst = ft_lstnew(0, 0);
		(*lst)->content = content;
		(*lst)->content_size = sizeof(t_file);
	}
	else
	{
		elem = (t_list*)ft_memalloc(sizeof(t_list));
		elem->content = content;
		elem->content_size = sizeof(t_file);
		lst_sort(elem, lst, flags);
	}
}
