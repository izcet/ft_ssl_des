/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:16:13 by irhett            #+#    #+#             */
/*   Updated: 2017/08/23 01:42:33 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BASE64_H
# define FT_BASE64_H

typedef struct		s_b64
{
	int				decode:2;
	char			*infile;
	char			*outfile;
	char			*string;
}					t_b64;

typedef struct s_com	t_com;

void				*base64_p(int argc, char **argv);
int					base64_e(t_com *command, void *data_t_b64);
void				base64_u(t_com *command);

void				*destroy_t_b64(t_b64 *data);

#endif
