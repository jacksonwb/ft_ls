/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 11:14:27 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/13 12:31:22 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"

# define FLAG_LOWER_L 1
# define FLAG_LOWER_A 2
# define FLAG_LOWER_R 4
# define FLAG_LOWER_T 8
# define FLAG_UPPER_R 16
# define FLAG_UPPER_G 32
# define FLAG_ERROR 32768

# define ATR_CONT_REG 32

# define P_MODE_ARG 2
# define P_MODE_DIR 4
# define P_MODE_DIR_ONLY 8

typedef struct			s_file
{
	char				*d_name;
	char				*d_path;
	struct stat			*stats;
}						t_file;

typedef struct			s_width
{
	size_t				w_link;
	size_t				w_uid;
	size_t				w_grp;
	size_t				w_size;
}						t_width;

typedef unsigned int	t_flags;

t_list					*dir_lst(DIR *dir_stream, char *path, t_flags flags);
void					ls_dir(char *path, char *name, t_flags flags);
void					free_lst(t_list *lst);
t_list					*arg_lst(int real_args, char **argv, t_flags flags);
int						ls_args(t_list *lst, int real_args, t_flags flags);

/*
** ls_sort
*/
void					lst_sort(t_list *new, t_list **head, t_flags flags);
void					lst_insert_after(t_list *new, t_list *lst);
int						alph_cmp(t_list *new, t_list *lst);
void					lst_helper(t_list **lst, t_file *content,
	t_flags flags);
int						t_flag_cmp(t_list *new, t_list *lst);
int						lst_cmp(t_list *new, t_list *lst, t_flags flags);

/*
** ls_print
*/
void					ls_print(t_list *lst, int mode);
void					write_file_l(t_list *lst, t_width *widths, char *name);
int						write_file(t_list *lst, int mode, t_width *widths);
void					write_link_dest(t_list *lst);
void					write_total(t_list *lst, t_width *widths);
char					*set_mode_bits(t_list *lst);
char					get_file_mode_char(t_list *lst);
char					*get_size_dev_str(t_list *lst);
void					get_passwd_str(char **uid_str, char **grp_str,
	t_list *lst);
char					get_file_mode_char(t_list *lst);
char					*set_mode_bits(t_list *lst);
void					get_passwd_str(char **uid_str, char **grp_str,
	t_list *lst);
char					*get_size_dev_str(t_list *lst);
int						get_correct_time_offset(t_list *lst);

/*
** ls_parse
*/
t_flags					set_flag(char *s);
t_flags					parse_args(int argc, char **argv);
int						count_real_args(int argc, char **argv);
int						is_r_dir(char *name);
char					*path_cat_helper(char *s1, char *s2);

/*
** utils
*/
char					*get_link_name(t_list *lst);
char					*get_link_name_color(t_list *lst);
char					*get_link_path(t_list *lst);
mode_t					get_link_mode(t_list *lst);
struct stat				*get_link_stats(t_list *lst);
time_t					get_link_t_sec(t_list *elem);
time_t					get_link_t_nsec(t_list *elem);
nlink_t					get_link_nlink(t_list *lst);
uid_t					get_link_uid(t_list *lst);
gid_t					get_link_gid(t_list *lst);
dev_t					get_link_rdev(t_list *lst);
off_t					get_link_size(t_list *lst);
blkcnt_t				get_link_blk(t_list *lst);
time_t					*get_link_t(t_list *elem);
int						is_link_exe(t_list *lst);
char					get_xattr_char(t_list *lst);

#endif
