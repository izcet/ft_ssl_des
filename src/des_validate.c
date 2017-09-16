/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 20:25:32 by irhett            #+#    #+#             */
/*   Updated: 2017/09/15 18:46:10 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define SORRY_FOR_NORM_HAX(foo, bar) free(foo); foo = bar

static void		des_rewrite_key(t_des *data, int len)
{
	int				i;
	int				k;
	unsigned char	*rewrite;

	while (data->key[len] && (k = ft_ishex(data->key[len])))
		len++;
	if (len && !data->key[len])
	{
		rewrite = (unsigned char *)ft_strnew(data->keylen);
		if (rewrite)
		{
			i = -1;
			while (++i < data->keylen)
			{
				rewrite[i] = get_hex_val(data->key[k - 1], data->key[k]);
				k += 2;
				if (k >= len)
					k = 1;
			}
			SORRY_FOR_NORM_HAX(data->key, rewrite);
			return ;
		}
	}
	SORRY_FOR_NORM_HAX(data->key, NULL);
}

int				des_validate_key(t_des *data)
{
	char	*temp;

	if (!data->key)
	{
		temp = getpass("enter des key in hex: ");
		data->key = (unsigned char *)ft_strdup(temp);
		ft_bzero(temp, ft_strlen(temp));
	}
	des_rewrite_key(data, 0);
	if (!data->key)
		return (com_err(data->c->name, "invalid hex key input."));
	return (0);
}

static void		des_rewrite_iv(t_des *data, int len)
{
	int				i;
	int				v;
	unsigned char	*rewrite;

	while (data->iv[len] && (v = ft_ishex(data->iv[len])))
		len++;
	if (len && !data->iv[len])
	{
		rewrite = (unsigned char *)ft_strnew(8);
		if (rewrite)
		{
			i = -1;
			while (++i < 8)
			{
				rewrite[i] = get_hex_val(data->iv[v - 1], data->iv[v]);
				v += 2;
				if (v >= len)
					v = 1;
			}
			SORRY_FOR_NORM_HAX(data->iv, rewrite);
			return ;
		}
	}
	SORRY_FOR_NORM_HAX(data->iv, NULL);
}

int				des_validate_iv(t_des *data)
{
	char	*temp;

	if (!data->iv)
	{
		temp = getpass("enter initial vector: ");
		data->iv = (unsigned char *)ft_strdup(temp);
		ft_bzero(temp, ft_strlen(temp));
	}
	des_rewrite_iv(data, 0);
	if (!data->iv)
		return (com_err(data->c->name, "invalid hex iv input."));
	return (0);
}
