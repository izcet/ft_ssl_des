/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:16:13 by irhett            #+#    #+#             */
/*   Updated: 2017/09/26 00:35:34 by irhett           ###   ########.fr       */
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
	unsigned char	*str;
	unsigned int	strlen;
}					t_des;

void				*desecb_p(t_com *command, int argc, char **argv);
int					desecb_e(t_com *command, void *data_t_des);
void				desecb_u(t_com *command);

void				*descbc_p(t_com *command, int argc, char **argv);
int					descbc_e(t_com *command, void *data_t_des);
void				descbc_u(t_com *command);

void				*des3ecb_p(t_com *command, int argc, char **argv);
int					des3ecb_e(t_com *command, void *data_t_des);
void				des3ecb_u(t_com *command);

void				*des3cbc_p(t_com *command, int argc, char **argv);
int					des3cbc_e(t_com *command, void *data_t_des);
void				des3cbc_u(t_com *command);


t_des				*create_t_des(t_com *command, int keylen, int v);
void				*destroy_t_des(t_des *data);

int					des_parse(int argc, char **argv, t_des *data);

int					des_validate_key(t_des *data);
int					des_validate_iv(t_des *data);

void				des_init_perm(unsigned char *eight);
void				des_final_perm(unsigned char *eight);

unsigned char		*des_get_left(unsigned char *block);
unsigned char		*des_get_right(unsigned char *block);
unsigned char		*des_zipper(unsigned char *left, unsigned char *right);

unsigned char		des_sbox(unsigned char sixbits, unsigned char *box);
unsigned char		*des_sbox_sub(unsigned char *bits);

unsigned char		*des_key_reduction(unsigned char *eight, int i_minus_one);
void				des_key_r_rot(unsigned char *key, int num);
void				des_key_l_rot(unsigned char *key, int num);
unsigned char		*des_get_subkey(unsigned char *key);

void				des_round(unsigned char *left, unsigned char *right, 
		unsigned char *subkey);

void				set_block(unsigned char *blockk, unsigned char *str,
		unsigned int i, unsigned int strlen);
unsigned char		*des_ecb_block(unsigned char *bk, unsigned char *ky, int d);
void				des_ecb_message(t_des *data);
void				des_cbc_message(t_des *data);
void				triple_des_message(t_des *data);
void				triple_des_cbc_message(t_des *data);

unsigned char		**init_des3_keys(unsigned char *key);
void				destroy_des3_keys(unsigned char **keys);
unsigned char		*des3_block(unsigned char *blk, unsigned char **key, int d);

void				test_des_print_key(unsigned char *eight);
void				test_des_print_subkey(unsigned char *seven);
void				test_des_print_roundkey(unsigned char *six);
void				test_print_num(unsigned char *arr, int len);

#endif
