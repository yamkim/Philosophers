#include "../incs/philo.h"

int
	ft_atoi(const char *nptr)
{
	long long	ret;
	int			sign;

	if (nptr == NULL)
		return (0);
	sign = 0;
	while (*nptr == '\f' || *nptr == '\n' || *nptr == '\r'
			|| *nptr == '\t' || *nptr == '\v' || *nptr == ' ')
		++nptr;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			++sign;
		++nptr;
	}
	ret = 0;
	while (*nptr >= 48 && *nptr <= 57)
		ret = ret * 10 + (long long)(*(nptr++) - '0');
	ret = sign % 2 == 0 ? ret : -ret;
	return ((int)ret);
}

static void
	print_nbr(unsigned int n, int fd)
{
	char	c;
	if (n >= 10)
		print_nbr(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void
	ft_putnbr_fd(int n, int fd)
{
	int				sign;
	unsigned int	n_tmp;

	if (fd < 0)
		return ;
	sign = n < 0 ? 1 : 0;
	if (sign)
	{
		write(fd, "-", 1);
		n_tmp = -n;
	}
	else
		n_tmp = n;
	print_nbr(n_tmp, fd);
}
