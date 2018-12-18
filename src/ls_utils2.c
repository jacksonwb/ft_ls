/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:48:39 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/12 20:51:53 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*get_link_path(t_list *lst)
{
	return (((t_file*)(lst->content))->d_path);
}

struct stat	*get_link_stats(t_list *lst)
{
	return (((t_file*)(lst->content))->stats);
}

nlink_t		get_link_nlink(t_list *lst)
{
	return ((((t_file*)(lst->content))->stats)->st_nlink);
}

off_t		get_link_size(t_list *lst)
{
	return ((((t_file*)(lst->content))->stats)->st_size);
}

blkcnt_t	get_link_blk(t_list *lst)
{
	return ((((t_file*)(lst->content))->stats)->st_blocks);
}
