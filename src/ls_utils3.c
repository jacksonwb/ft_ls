/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:46:58 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/13 12:32:56 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			is_link_exe(t_list *lst)
{
	mode_t	mode;

	mode = get_link_mode(lst);
	if ((S_IXUSR & mode) || (S_IXGRP & mode) || (S_IXOTH & mode))
		return (1);
	else
		return (0);
}

void		free_lst(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(get_link_name(lst));
		free(get_link_path(lst));
		free(get_link_stats(lst));
		free((t_file*)(lst->content));
		free(lst);
		lst = next;
	}
}

char		*get_link_name_color(t_list *lst)
{
	char		*name;
	char		*s;
	static char color[7] = "\e[39m";
	static char end[6] = "\e[0m";

	if (S_ISDIR(get_link_mode(lst)))
		color[3] = '4';
	if (S_ISLNK(get_link_mode(lst)))
		color[3] = '5';
	else if (S_ISBLK(get_link_mode(lst)) || S_ISCHR(get_link_mode(lst)))
		color[3] = '3';
	else if (S_ISFIFO(get_link_mode(lst)) && (color[2] = '4'))
		color[3] = '3';
	else if (S_ISSOCK(get_link_mode(lst)))
		color[3] = '6';
	else if (S_ISREG(get_link_mode(lst)) && is_link_exe(lst))
		color[3] = '1';
	s = ft_strjoin(color, ((t_file*)(lst->content))->d_name);
	name = ft_strjoin(s, end);
	color[2] = '3';
	color[3] = '9';
	free(s);
	return (name);
}

char		get_xattr_char(t_list *lst)
{
	acl_t	acl;
	char	c;

	acl = acl_get_link_np(get_link_path(lst), ACL_TYPE_EXTENDED);
	if (listxattr(get_link_path(lst), NULL, 0, XATTR_NOFOLLOW))
		c = '@';
	else if (acl)
		c = '+';
	else
		c = ' ';
	if (acl)
		acl_free(acl);
	return (c);
}
