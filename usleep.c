#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long	ft_get_time_in_mcs(void)
{
	long timestamp;
	struct timeval time;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000000) + time.tv_usec;
	return (timestamp);
}

void	ft_usleep(long time, long diff1)
{
	long	diff;
	long	timestamp;
	long	ret;

	timestamp = ft_get_time_in_mcs();
	while (1)
	{
		diff = ft_get_time_in_mcs() - timestamp;
		if (diff > time)
		{
			// printf("diff: %ld\n", diff);
			// printf("diff - time: %ld\n", diff - time);
			break ;
		}
		usleep(10);
	}
	// while (1)
	// {
	// 	diff = ft_get_time_in_mcs() - timestamp;
	// 	if (time > diff)
	// 	{
	// 		// printf("diff: %ld\n", diff);
	// 		// printf("time - diff: %ld\n", time - diff);
	// 		// usleep(time - diff);
	// 		usleep(time);
	// 	}
	// 	break ;
	// }
}

int main(void)
{
	int i;
	long diff;
	long timestamp;

	timestamp = ft_get_time_in_mcs();
	i = -1;
	while (++i < 10)
	{
		diff = ft_get_time_in_mcs() - timestamp;
		printf("time : %ld\n", diff);
		ft_usleep(1000, diff);
		// usleep(1000);
	}
	return (0);
}