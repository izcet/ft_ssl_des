/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftssl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:16:13 by irhett            #+#    #+#             */
/*   Updated: 2017/11/22 14:40:37 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSSL_H
# define FTSSL_H

# include <fcntl.h>
# include <pwd.h>

# include "libft.h"

# include "ft_base64.h"
# include "ft_des.h"

# define NUM_COMMAND_TYPES	3

typedef struct		s_com
{
	char			*name;
	void			*parse;
	void			*exec;
	void			*usage;
}					t_com;

typedef struct		s_wrap
{
	char			*name;
	unsigned int	num;
	t_com			*list;
}					t_wrap;

typedef struct		s_output
{
	char			*com;
	char			*file;
	char			*str;
	unsigned int	strlen;
	char			newline:2;
}					t_output;

t_wrap				*init_commands(void);
void				delete_commands(t_wrap *commands);
void				print_command_list(t_wrap *commands, char *error);

int					interpret(char *name, int argc, char **argv, t_wrap *coms);
int					call_command(t_com *command, int argc, char **argv);

int					com_err(char *command, char *err);
int					com_err_2(char *command, char *err, char *val);
int					com_err_3(char *command, char *err, char *val, char *end);

int					write_to_file(t_output *output);
int					write_to_stdout(char *str, int strlen, char b64, char dec);
unsigned char		*read_data(char *file, char *invoker, unsigned int *len);

void				swap_ptr(void **a, void **b);
void				swap_int(int *a, int *b);

unsigned char		get_hex_val(char big, char smol);
int					ft_ishex(char c);

unsigned char		*raw_append(unsigned char *str, unsigned char *other,
		unsigned int strlen, unsigned int otherlen);
unsigned char		*raw_clone(unsigned char *str, unsigned int strlen);
unsigned char		*raw_expand(unsigned char *str, unsigned char *extra,
		unsigned int strlen, unsigned int otherlen);
void				raw_xor(unsigned char *s, unsigned char *o, unsigned int l);
void				raw_copy(unsigned char *dst, unsigned char *src,
		unsigned int l);

void				free_set(void *prev, void *next);

#endif
