/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:47:44 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/12 20:51:45 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

mode_t	get_link_mode(t_list *lst)
{
	return ((((t_file*)(lst->content))->stats)->st_mode);
}

dev_t	get_link_rdev(t_list *lst)
{
	return ((((t_file*)(lst->content))->stats)->st_rdev);
}

uid_t	get_link_uid(t_list *lst)
{
	return ((((t_file*)(lst->content))->stats)->st_uid);
}

gid_t	get_link_gid(t_list *lst)
{
	return ((((t_file*)(lst->content))->stats)->st_gid);
}

char	*get_link_name(t_list *lst)
{
	return (((t_file*)(lst->content))->d_name);
}
