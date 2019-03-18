## Millsecond

```C++
#include   <time.h> 
#include   <stdio.h> 
#include   <conio.h> 

int  main() 
{ 
 	 clock_t t_begin,t_end; 
  
  	//代码1开始计时 
  	t_begin=clock(); 
	// 

	//你的程序段 

	// 
  	t_end=clock(); 
  	printf( "代码所用的时间:%f毫秒/n ",(double)(t_end-t_begin)); 
	getch(); 
	return   0; 
} 

```

