/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:16:13 by irhett            #+#    #+#             */
/*   Updated: 2017/09/14 10:02:55 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DES_H
# define FT_DES_H

# include "ft_des_num.h"

typedef struct s_com	t_com;

typedef struct		s_des
{
	int				decode:2;
	int				base64:2;
	char			*infile;
	char			*outfile;
	unsigned char	*key;
	char			keylen; // 8 for 1 key, 24 for 3 keys
	int				v:2;
	unsigned char	*iv;
	t_com			*c;
	unsigned int	strlen;
}					t_des;

void				*desecb_p(t_com *command, int argc, char **argv);
int					desecb_e(t_com *command, void *data_t_des);
void				desecb_u(t_com *command);

void				*descbc_p(t_com *command, int argc, char **argv);
int					descbc_e(t_com *command, void *data_t_des);
void				descbc_u(t_com *command);

void				*des3_p(t_com *command, int argc, char **argv);
int					des3_e(t_com *command, void *data_t_des);
void				des3_u(t_com *command);

t_des				*create_t_des(t_com *command, int keylen);
void				*destroy_t_des(t_des *data);

int					des_parse(int argc, char **argv, t_des *data);

int					des_validate_key(t_des *data);
int					des_validate_iv(t_des *data);

void				des_init_perm(char *eight);
void				des_final_perm(char *eight);

unsigned char		des_sbox(unsigned char sixbits, unsigned char *box);
unsigned char		*des_sbox_sub(unsigned char *bits);

void				des_xor(unsigned char *s, unsigned char *o, unsigned int l);

/*
** counter used here should always called with a -1
** this is simply a norm hack, not significant
*/
unsigned char		*des_key_reduction(unsigned char *eight, int counter);
void				des_key_r_rot(unsigned char *key, int num);
void				des_key_l_rot(unsigned char *key, int num);
unsigned char		*des_get_subkey(unsigned char *key);

/*
** right remains untouched
** left is modified by xor
** retain their original positions, not swapped
*/
void				des_round(unsigned char *left, unsigned char *right, 
		unsigned char *subkey);
unsigned char		*des_work(t_des *data);

#endif
