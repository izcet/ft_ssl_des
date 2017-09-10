/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:16:13 by irhett            #+#    #+#             */
/*   Updated: 2017/09/09 16:24:29 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BASE64_H
# define FT_BASE64_H

# define KY64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
# define BASE64_KEY KY64


typedef struct s_com	t_com;

typedef struct		s_b64
{
	int				decode:2;
	char			*infile;
	char			*outfile;
	char			*string;
	t_com			*c;
}					t_b64;



void				*base64_p(t_com *command, int argc, char **argv);
int					base64_e(t_com *command, void *data_t_b64);
void				base64_u(t_com *command);

char				*base64_encode(char *string, char *key);
char				*base64_decode(char *string, char *key);

void				*destroy_t_b64(t_b64 *data);

#endif
