## Local Time

```C++
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define N 10

int main(int argc,char *argv[])
{ 
	char buf[N];
	
	time_t t;
	time(&t);
	struct tm *t1;
	t1=localtime(&t);
	sprintf(buf,"%d/ %d/ %d %d:%d:%d\n",t1->tm_year+1900,
                              			 t1->tm_mon+1,
										 t1->tm_mday,
										 t1->tm_hour,
										 t1->tm_min,
										 t1->tm_sec),
   
	printf("%s",buf);
}

```

