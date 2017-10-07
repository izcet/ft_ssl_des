/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 23:38:04 by irhett            #+#    #+#             */
/*   Updated: 2017/09/26 00:11:02 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void	*des3_p(t_com *command, int argc, char **argv)
{
	t_des	*data;

	data = create_t_des(command, 24, 0);
	if (!data)
		return (NULL);
	if (des_parse(argc, argv, data))
		return (destroy_t_des(data));
	if (des_validate_key(data))
		return (destroy_t_des(data));
	return (data);
}
