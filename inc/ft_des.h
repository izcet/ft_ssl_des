/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:16:13 by irhett            #+#    #+#             */
/*   Updated: 2017/08/27 16:08:53 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DES_H
# define FT_DES_H

typedef struct		s_des
{
	int				decode:2;
	int				base64:2;
	char			*infile;
	char			*outfile;
	char			*key;
}					t_des;

typedef struct s_com	t_com;

void				*desecb_p(t_com *command, int argc, char **argv);
int					desecb_e(t_com *command, void *data_t_des);
void				desecb_u(t_com *command);

void				*descbc_p(t_com *command, int argc, char **argv);
int					descbc_e(t_com *command, void *data_t_des);
void				descbc_u(t_com *command);

void				des_init_perm(char *eight);
void				des_final_perm(char *eight);

#endif
