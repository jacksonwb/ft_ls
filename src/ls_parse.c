/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:43:07 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/12 21:45:50 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags		set_flag(char *s)
{
	int			val;
	t_flags		flags;
	static char	key[] = "lartRG";

	flags = 0;
	while (*s)
	{
		if (ft_strchr(key, *s))
			val = ft_strchr(key, *s) - key;
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n", *s);
			ft_printf("usage: ls [-GRalrt] [file ...]\n");
			return (FLAG_ERROR);
		}
		flags |= pow_of_2(val);
		++s;
	}
	return (flags);
}

t_flags		parse_args(int argc, char **argv)
{
	int		i;
	t_flags	flags;

	i = 1;
	flags = 0;
	while (i < argc && *argv[i] == '-')
	{
		flags |= set_flag(argv[i] + 1);
		if (flags & FLAG_ERROR)
			return (flags);
		i++;
	}
	return (flags);
}

int			count_real_args(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc && *argv[i] == '-')
		i++;
	return (argc - i);
}

int			is_r_dir(char *name)
{
	if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (0);
	else
		return (1);
}

char		*path_cat_helper(char *s1, char *s2)
{
	char	*ptr;
	char	*new;

	if (s1[ft_strlen(s1) - 1] != '/')
		ptr = ft_strjoin(s1, "/");
	else
		ptr = ft_strdup(s1);
	new = ft_strjoin(ptr, s2);
	free(ptr);
	return (new);
}
