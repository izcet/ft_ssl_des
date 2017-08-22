/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftssl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:16:13 by irhett            #+#    #+#             */
/*   Updated: 2017/08/21 19:07:44 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSSL_H
# define FTSSL_H

# include "libft.h"

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
	t_com			*list;
	char			*name;
	unsigned int	num;
}					t_wrap;

t_wrap				*init_commands(void);
void				delete_commands(t_wrap *commands);
void				print_command_list(t_wrap *commands);

void				interpret(char *name, int argc, char **argv, t_wrap *coms);
void				call_command(t_com command, int argc, char **argv);

#endif
