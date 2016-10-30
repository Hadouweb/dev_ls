/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:22:09 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:22:10 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_error_errno(char *str)
{
	ft_putstr_fd("ls: ", 2);
	if (str != NULL)
		perror(str);
	else
		perror("");
}

void	ls_error(char *str)
{
	if (str != NULL)
		ft_putendl_fd(str, 2);
	else
		ft_putendl_fd("Error", 2);
	exit(1);
}
