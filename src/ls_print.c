/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:45:22 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/13 12:55:46 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	write_total(t_list *lst, t_width *widths)
{
	blkcnt_t	blocks;
	char		*uid_str;
	char		*grp_str;
	char		*size_str;

	blocks = 0;
	while (lst)
	{
		blocks += get_link_blk(lst);
		get_passwd_str(&uid_str, &grp_str, lst);
		widths->w_uid = MAX(widths->w_uid, ft_strlen(uid_str));
		widths->w_grp = MAX(widths->w_grp, ft_strlen(grp_str));
		size_str = get_size_dev_str(lst);
		widths->w_size = MAX(widths->w_size, ft_strlen(size_str));
		widths->w_link = MAX(widths->w_link, itoa_len(get_link_nlink(lst)));
		free(uid_str);
		free(grp_str);
		free(size_str);
		lst = lst->next;
	}
	ft_printf("total %d\n", blocks);
}

void	ls_print(t_list *lst, int mode)
{
	static int		has_written = 0;
	static t_width	widths;

	ft_bzero(&widths, sizeof(widths));
	if (mode & P_MODE_DIR_ONLY)
	{
		if (has_written)
			ft_printf("\n");
		has_written |= ft_printf("%s:\n", get_link_name(lst));
		return ;
	}
	else if (mode & FLAG_LOWER_L)
		write_total(lst, &widths);
	while (lst && !(mode & P_MODE_DIR_ONLY))
	{
		if (mode & P_MODE_ARG)
		{
			if (!S_ISDIR(get_link_mode(lst)))
				has_written |= write_file(lst, mode, &widths);
		}
		else
			has_written |= write_file(lst, mode, &widths);
		lst = lst->next;
	}
}

int		write_file(t_list *lst, int mode, t_width *widths)
{
	char *name;

	if (mode & FLAG_UPPER_G)
		name = get_link_name_color(lst);
	else
		name = ft_strdup(get_link_name(lst));
	if (mode & FLAG_LOWER_L)
		write_file_l(lst, widths, name);
	else
		ft_printf("%s\n", name);
	free(name);
	return (1);
}

void	write_link_dest(t_list *lst)
{
	ssize_t			status;
	static size_t	bufsize = 1000;
	static char		buf[1000];

	status = readlink(get_link_path(lst), buf, bufsize);
	ft_printf(" -> %.*s\n", status, buf);
}

void	write_file_l(t_list *lst, t_width *widths, char *name)
{
	char	*s;
	char	*uid_str;
	char	*grp_str;
	char	*size_str;
	char	*time_str;

	s = ft_strsub(set_mode_bits(lst), 0, 12);
	get_passwd_str(&uid_str, &grp_str, lst);
	size_str = get_size_dev_str(lst);
	time_str = ft_strdup(ctime(get_link_t(lst)));
	ft_printf("%s%c %*u %-*s  %-*s  %*s %.3s %.2s %.5s %s", s,
	get_xattr_char(lst), widths->w_link, get_link_nlink(lst), widths->w_uid,
	uid_str, widths->w_grp, grp_str, widths->w_size, size_str, time_str + 4,
		time_str + 8, time_str + get_correct_time_offset(lst), name);
	if (S_ISLNK(get_link_mode(lst)))
		write_link_dest(lst);
	else
		ft_printf("\n");
	free(uid_str);
	free(grp_str);
	free(time_str);
	free(s);
	free(size_str);
}
