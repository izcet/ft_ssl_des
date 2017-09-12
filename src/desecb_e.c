/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/09/11 22:29:28 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int		desecb_e(t_com *command, void *data_t_des)
{
	t_des	*data;
	char	*message;
	int		ret;

	ret = 0;
	data = (t_des *)data_t_des;
	data->c = command;
	message = des_get_message(data);
	if (data->outfile)
		ret = write_to_file(message, data->outfile, command->name);
	else
		ft_putstr(message);
	free(message);
	destroy_t_des(data);
	return (ret);
}
