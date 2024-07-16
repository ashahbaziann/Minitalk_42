/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:29 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/07/15 18:53:14 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

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

void	ft_putnbr(int nb)
{
	char	c;

	if (nb == -2147483648)
	{
		write (1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -1 * nb;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		c = '0' + (nb % 10);
		write (1, &c, 1);
	}
	else
	{
		c = '0' + nb;
		write (1, &c, 1);
	}
}

void	check(int flag, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;

	(void)info;
	(void)context;
	if (flag == 1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write (1, &i, 1);
		bit = 0;
		i = 0;
	}
}

void	handler(int flag, siginfo_t *info, void *context)
{
	if (flag == SIGUSR1)
		check(1, info, context);
	else
		check(0, info, context);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					i;

	i = 0;
	(void)argv;
	if (argc != 1)
		error ("Invalid arguments!\n");
	ft_putnbr(getpid());
	write (1, "\n", 1);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
