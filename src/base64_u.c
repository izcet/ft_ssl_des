/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:39:18 by irhett            #+#    #+#             */
/*   Updated: 2017/08/22 16:46:41 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void		base64_u(t_com *command)
{
	(void)command;
	ft_putendl("base64: Usage: [-e | -d] [-i infile] [-o outfile]");
	ft_putendl("  -e, encode (default behavior)");
	ft_putendl("  -d, decode");
	ft_putendl("  -i, input file (\"-\" or default: stdin)");
	ft_putendl("  -o, output file (\"-\" or default: stdout)");
}
