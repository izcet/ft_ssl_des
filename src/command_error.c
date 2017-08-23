/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 23:12:04 by irhett            #+#    #+#             */
/*   Updated: 2017/08/23 01:35:44 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int		com_err(char *command, char *error)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Error: ", 2);
	ft_putendl_fd(error, 2);
	return (1);
}

int		com_err_2(char *command, char *error, char *val)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(val, 2);
	return (1);
}

int		com_err_3(char *command, char *error, char *val, char *end)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(val, 2);
	ft_putendl_fd(end, 2);
	return (1);
}
