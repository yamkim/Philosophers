#include "../incs/philo.h"

sem_t
	*ft_sem_open(char *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}
