/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:35 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/07/15 19:08:03 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	error(char *line)
{
	if (!line)
		return ;
	while (*line)
	{
		write (1, line, 1);
		line++;
	}
	exit(1);
}

void	process_message(int pid, char *str)
{
	int				bit;
	int				flag;

	while (*str)
	{
		bit = 0;
		while (bit < 8)
		{
			if (*str & (1 << bit))
				flag = kill(pid, SIGUSR1);
			else
				flag = kill(pid, SIGUSR2);
			if (flag == -1)
				error("CLIENT: Error!\n");
			usleep(70);
			bit++;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		error("Invalid arguments!\n");
	pid = ft_atoi(argv[1]);
	process_message(pid, argv[2]);
	process_message(pid, "\n");
	exit(0);
}
