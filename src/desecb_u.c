/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:39:18 by irhett            #+#    #+#             */
/*   Updated: 2017/09/11 17:13:52 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void		desecb_u(t_com *command)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(command->name, 2);
	ft_putendl_fd(" [-e|-d] [-a] [-k key] [-i|-in file] [-o|-out file]", 2);
	ft_putendl_fd("  -e, encode (default behavior)", 2);
	ft_putendl_fd("  -d, decode", 2);
	ft_putendl_fd("  -a, base64 encode/decode, depending on previous flag", 2);
	ft_putendl_fd("  -i, -in, input file (\"-\" or default: stdin)", 2);
	ft_putendl_fd("  -o, -out, output file (\"-\" or default: stdout)", 2);
	ft_putendl_fd("  -k, key (64 bits, hexadecimal)", 2);
}
