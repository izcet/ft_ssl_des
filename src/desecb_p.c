/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:55:31 by irhett            #+#    #+#             */
/*   Updated: 2017/09/15 18:01:43 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void		*desecb_p(t_com *command, int argc, char **argv)
{
	t_des	*data;

	data = create_t_des(command, 8, 0);
	if (!data)
		return (NULL);
	if (des_parse(argc, argv, data))
		return (destroy_t_des(data));
	if (des_validate_key(data))
		return (destroy_t_des(data));
	return (data);
}
