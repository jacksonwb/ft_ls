/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 11:15:27 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/13 12:29:56 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_dir(char *path, char *name, t_flags flags)
{
	DIR		*dir_stream;
	t_list	*lst;
	t_list	*head;

	if (!(dir_stream = opendir(path)))
	{
		ft_printf("ft_ls: %s: ", name);
		perror(NULL);
		return ;
	}
	lst = dir_lst(dir_stream, path, flags);
	head = lst;
	closedir(dir_stream);
	ls_print(lst, P_MODE_DIR + (flags & FLAG_LOWER_L) + (flags & FLAG_UPPER_G));
	if (flags & FLAG_UPPER_R)
		while (lst)
		{
			if (S_ISDIR(get_link_mode(lst)) && is_r_dir(get_link_name(lst)))
			{
				ft_printf("\n%s:\n", get_link_path(lst));
				ls_dir(get_link_path(lst), get_link_name(lst), flags);
			}
			lst = lst->next;
		}
	free_lst(head);
}

t_list		*dir_lst(DIR *dir_stream, char *path, t_flags flags)
{
	struct dirent	*file;
	t_file			*new;
	t_list			*lst;
	int				status;

	lst = NULL;
	while ((file = readdir(dir_stream)))
	{
		if (file->d_name[0] != '.' || flags & FLAG_LOWER_A)
		{
			new = (t_file*)ft_memalloc(sizeof(t_file));
			new->stats = (struct stat*)ft_memalloc(sizeof(struct stat));
			new->d_name = ft_strdup(file->d_name);
			new->d_path = path_cat_helper(path, new->d_name);
			status = lstat(new->d_path, new->stats);
			lst_helper(&lst, new, flags);
		}
	}
	return (lst);
}

/*
**Takes the argv list, advanced to the first real file argument
**and adds all files and stats to a sorted list.
*/

t_list		*arg_lst(int real_args, char **argv, t_flags flags)
{
	t_file	*new;
	t_list	*lst;
	int		i;
	int		status;

	lst = NULL;
	i = 0;
	while (i < real_args)
	{
		new = (t_file*)ft_memalloc(sizeof(t_file));
		new->d_name = ft_strsub(argv[i], 0, ft_strlen(argv[i]));
		new->d_path = ft_strdup(new->d_name);
		new->stats = (struct stat*)(ft_memalloc(sizeof(struct stat)));
		status = (flags & FLAG_LOWER_L && new->d_name[ft_strlen(new->d_name)] !=
		'/') ? lstat(new->d_name, new->stats) : stat(new->d_name, new->stats);
		if (!status)
			lst_helper(&lst, new, flags);
		else
		{
			ft_printf("ft_ls: %s: ", new->d_name);
			perror(0);
		}
		++i;
	}
	return (lst);
}

/*
** Print the files lst with the args level print mode, and recurse if called for
** Add the flags argument!
*/

int			ls_args(t_list *lst, int real_args, t_flags flags)
{
	t_list	*head;

	head = lst;
	if (real_args == 1 && lst && S_ISDIR(get_link_mode(lst)))
		ls_dir(get_link_name(lst), get_link_name(lst), flags);
	else
	{
		ls_print(lst, P_MODE_ARG + (flags & FLAG_LOWER_L) +
			(flags & FLAG_UPPER_G));
		while (lst)
		{
			if (S_ISDIR(get_link_mode(lst)))
			{
				ls_print(lst, P_MODE_DIR_ONLY);
				ls_dir(get_link_path(lst), get_link_name(lst), flags);
			}
			lst = lst->next;
		}
	}
	free_lst(lst);
	return (0);
}

int			main(int argc, char **argv)
{
	t_flags	flags;
	t_list	*lst;
	int		real_args;

	flags = parse_args(argc, argv);
	if (flags & FLAG_ERROR)
		return (1);
	if (!(real_args = count_real_args(argc, argv)))
		ls_dir(".", ".", flags);
	else
	{
		lst = arg_lst(real_args, argv + (argc - real_args), flags);
		ls_args(lst, real_args, flags);
	}
	return (0);
}
