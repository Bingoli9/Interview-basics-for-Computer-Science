## Nanosecond

```C++
int gettimeofday(struct timeval* tv, struct timezone* tz)
```

```C++
struct timezone{
int tz_minuteswest;/*格林威治时间往西方的时差*/
int tz_dsttime;/*DST 时间的修正方式*/
}
```

```C++
struct timeval{
long int tv_sec; // 秒数
long int tv_usec; // 微秒数
}
```

example

```C++
#include <stdio.h>        // for printf()
#include <sys/time.h>    // for gettimeofday()
#include <unistd.h>        // for sleep()
 
int main()
{
    struct timeval start, end;
    gettimeofday( &start, NULL );
    printf("start : %d.%d\n", start.tv_sec, start.tv_usec);
    sleep(1);
    gettimeofday( &end, NULL );
    printf("end   : %d.%d\n", end.tv_sec, end.tv_usec);
 
    return 0;
}
```

