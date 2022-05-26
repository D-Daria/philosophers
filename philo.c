#include <unistd.h>
#include <stdio.h>
# include <sys/time.h>

struct timeval start;

void    handler(int i)
{
    printf("In Handler %d\n",i);
    struct timeval current_time;
    long tm_start = (start.tv_sec * 1000000) + start.tv_usec;
    gettimeofday(&current_time,0);
    long tm_current = (current_time.tv_sec * 1000000) + current_time.tv_usec;
    printf("%ldms: emulation begins\n", tm_current - tm_start);
    return;
}

long long get_time(void)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long long tm = (current_time.tv_sec * 1000000) + current_time.tv_usec;
    return (tm);
}

void ft_usleep(long long time)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long long tm = (current_time.tv_sec * 1000000) + current_time.tv_usec;

    printf("tm: %lld\n", tm);
    printf("get_time: %lld\n", get_time());
    printf("diff: %lld\n", tm - get_time());

    while (1)
    {
        if (get_time() - tm >= time)
            break ;
        usleep(5);
    }
}

int main()
{
    struct timeval current_time;
    int i=0;
    gettimeofday(&start,0);
    long tm_start = (start.tv_sec * 1000000) + start.tv_usec;
    gettimeofday(&current_time, 0);
    long tm_current = (current_time.tv_sec * 1000000) + current_time.tv_usec;
    printf("%ldms: emulation begins\n", tm_current - tm_start);

    while(i++ < 5)
    {
        // usleep(10000); // compare with usleep(1000000)
        ft_usleep(100000); // compare with usleep(1000000)
        handler(i);
    }
    return 0;
}