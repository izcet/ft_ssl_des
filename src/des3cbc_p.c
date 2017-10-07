/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3cbc_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 00:34:14 by irhett            #+#    #+#             */
/*   Updated: 2017/10/07 15:47:35 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void	*des3cbc_p(t_com *command, int argc, char **argv)
{
	t_des	*data;

	data = create_t_des(command, 24, 1);
	if (!data)
		return (NULL);
	if (des_parse(argc, argv, data))
		return (destroy_t_des(data));
	if (des_validate_key(data))
		return (destroy_t_des(data));
	if (des_validate_iv(data))
		return (destroy_t_des(data));
	return (data);
}
