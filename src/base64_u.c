/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:39:18 by irhett            #+#    #+#             */
/*   Updated: 2017/08/23 01:39:52 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void		base64_u(t_com *command)
{
	(void)command;
	ft_putendl_fd("base64: Usage: [-e | -d] [-i infile] [-o outfile]", 2);
	ft_putendl_fd("  -e, encode (default behavior)", 2);
	ft_putendl_fd("  -d, decode", 2);
	ft_putendl_fd("  -i, input file (\"-\" or default: stdin)", 2);
	ft_putendl_fd("  -o, output file (\"-\" or default: stdout)", 2);
}
