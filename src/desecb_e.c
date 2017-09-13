/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 00:25:42 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int		desecb_e(t_com *c, void *data_t_des)
{
	t_des	*data;
	char	*message;
	int		ret;

	ret = 0;
	data = (t_des *)data_t_des;
	data->c = c;
	message = des_get_message(data);
	if (data->outfile)
		ret = write_to_file(message, data->outfile, c->name, data->strlen);
	else
	{
		write(1, message, data->strlen);
		ft_putchar('\n');
	}
	free(message);
	destroy_t_des(data);
	return (ret);
}
