/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:27:34 by efranco           #+#    #+#             */
/*   Updated: 2025/03/26 00:28:04 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_atoi(const char *theString)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((theString[i] >= 9 && theString[i] <= 13) || (theString[i] == 32))
		i++;
	if (theString[i] == '-' || theString[i] == '+')
	{
		if (theString[i] == '-')
			sign *= -1;
		i++;
	}
	while (theString[i] >= '0' && theString[i] <= '9' && theString[i])
	{
		res = res * 10 + (theString[i] - 48);
		i++;
	}
	return (res * sign);
}
long ft_atol(const char *theString)
{
	long	i;
	long	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((theString[i] >= 9 && theString[i] <= 13) || (theString[i] == 32))
		i++;
	if (theString[i] == '-' || theString[i] == '+')
	{
		if (theString[i] == '-')
			sign *= -1;
		i++;
	}
	while (theString[i] >= '0' && theString[i] <= '9' && theString[i])
	{
		res = res * 10 + (theString[i] - 48);
		i++;
	}
	return (res * sign);
}
int ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	else
		return (0);
}
