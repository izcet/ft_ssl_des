/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/08/22 18:01:06 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int		desecb_e(t_com *command, void *data_t_des)
{
	t_des	*data;

	(void)command;
	data = (t_des *)data_t_des;
	free(data);
	return (0);
}
