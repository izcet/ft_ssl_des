/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 22:24:44 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int		desecb_e(t_com *c, void *data_t_des)
{
	t_des			*data;
	unsigned char	*str;
	int				ret;

	ret = 0;
	data = (t_des *)data_t_des;
	data->c = c;
	str = des_work(data);
	//printf("here\n");
	if (data->outfile)
		ret = write_to_file((char *)str, data->outfile, c->name, data->strlen);
	else
	{
		write(1, str, data->strlen);
		ft_putchar('\n');
	}
	free(str);
	destroy_t_des(data);
	return (ret);
}
