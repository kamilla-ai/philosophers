/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:49:38 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/16 20:23:06 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	skip_whitespace_and_get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' ')
	{
		(*i)++;
	}
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	convert_str_to_num(const char *str, int *i, int *sign)
{
	int	num;

	num = 0;
	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	while (str[*i])
	{
		if ((str[*i] >= '0' && str[*i] <= '9'))
		{
			if ((*sign == 1 && num > 2147483647 / 10) || (*sign == 1
					&& num == 2147483647 / 10 && str[*i] > '7'))
				return (-1);
			else if ((*sign == -1 && num > 2147483647 / 10) || (*sign == -1
					&& num == 2147483647 / 10 && str[*i] > '8'))
				return (-1);
			num = num * 10 + (str[*i] - '0');
			(*i)++;
		}
		else if (str[*i] == ' ')
			(*i)++;
		else
			return (-1);
	}
	return (num);
}

int	ph_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	num = 0;
	sign = 1;
	sign = skip_whitespace_and_get_sign(str, &i);
	num = convert_str_to_num(str, &i, &sign);
	num = num * sign;
	return (num);
}
