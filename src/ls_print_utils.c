/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:37:02 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/13 10:36:27 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	get_file_mode_char(t_list *lst)
{
	mode_t	mode;

	mode = get_link_mode(lst);
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return (0);
}

char	*set_mode_bits(t_list *lst)
{
	mode_t				mode;
	static char			bits[12];
	static const char	*template[] = {"---", "--x", "-w-", "-wx",
		"r--", "r-x", "rw-", "rwx"};

	mode = get_link_mode(lst);
	bits[0] = get_file_mode_char(lst);
	ft_strcpy(&bits[1], template[(mode >> 6) & 7]);
	ft_strcpy(&bits[4], template[(mode >> 3) & 7]);
	ft_strcpy(&bits[7], template[(mode & 7)]);
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXOTH) ? 't' : 'T';
	bits[11] = '\0';
	return (bits);
}

void	get_passwd_str(char **uid_str, char **grp_str, t_list *lst)
{
	struct passwd	*usr_info;
	struct group	*grp_info;

	usr_info = getpwuid(get_link_uid(lst));
	if (!usr_info || !usr_info->pw_name)
		*uid_str = ft_itoa(get_link_uid(lst));
	else
		*uid_str = ft_strsub(usr_info->pw_name, 0,
			ft_strlen(usr_info->pw_name));
	grp_info = getgrgid(get_link_gid(lst));
	if (!grp_info || !grp_info->gr_name)
		*grp_str = ft_itoa(get_link_gid(lst));
	else
		*grp_str = ft_strsub(grp_info->gr_name, 0,
			ft_strlen(grp_info->gr_name));
}

char	*get_size_dev_str(t_list *lst)
{
	char	*s1;
	char	*size_str;
	char	*major;
	char	*minor;

	if (S_ISBLK(get_link_mode(lst)) || S_ISCHR(get_link_mode(lst)))
	{
		major = ft_itoa(major(get_link_rdev(lst)));
		minor = ft_itoa(minor(get_link_rdev(lst)));
		s1 = ft_strjoin(major, ", ");
		size_str = ft_strjoin(s1, minor);
		free(major);
		free(s1);
		free(minor);
	}
	else
		size_str = ft_itoa(get_link_size(lst));
	return (size_str);
}

int		get_correct_time_offset(t_list *lst)
{
	time_t	file_time;
	time_t	now;

	file_time = get_link_t_sec(lst);
	now = time(NULL);
	if (ft_abs(now - file_time) > 15778463)
		return (19);
	else
		return (11);
}
