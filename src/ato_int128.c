/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ato_int128.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:10:37 by juan-aga          #+#    #+#             */
/*   Updated: 2023/06/05 16:10:38 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "push_swap_utils.h"

__int128	ft_ato_int128(char *str)
{
	int			i;
	int			sign;
	__int128	result;

	sign = 1;
	result = 0;
	i = 0;
	if (ft_issign(str[i]))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}
