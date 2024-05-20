#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		printf("av[%d]: [%s]\n", i, av[i]);
		i++;
	}
	av++;
	execv("/bin/LS", av);
}