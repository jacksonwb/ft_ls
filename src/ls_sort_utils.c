/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:39:15 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/12 21:41:38 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

time_t	get_link_t_sec(t_list *elem)
{
	return ((((t_file*)(elem->content))->stats)->st_mtimespec.tv_sec);
}

time_t	*get_link_t(t_list *elem)
{
	return (&((((t_file*)(elem->content))->stats)->st_mtimespec.tv_sec));
}

time_t	get_link_t_nsec(t_list *elem)
{
	return ((((t_file*)(elem->content))->stats)->st_mtimespec.tv_nsec);
}

int		alph_cmp(t_list *new, t_list *lst)
{
	if (lst == NULL)
		return (0);
	return (ft_strcmp(get_link_name(new), get_link_name(lst)));
}
