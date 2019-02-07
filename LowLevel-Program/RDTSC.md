## RDTSC

TSC is a register used for timer, and it will add one in every clock signal.  

We can calculate the computer dominant frequency with TSC. Besides calculate CPU dominant frequency, TSC can also  
be used to test other computer unit speed.  


```C++
#define rdtsc(low,high) /
	   __asm__ __volatile__ ("rdtsc":"=a"(low), "=d"(high))
	   
#define rdtscl(low) /
       __asm__ __volatile__("rdtsc" : "=a" (low) : : "edx")
  
#define rdtscll(val) /
       __asm__ __volatile__("rdtsc" : "=A" (val))
	
```

The third macro can be used to apply a us-timer function: 
```C++
typedef unsigned long long cycles_t;
inline cycles_t currentcycles() {
	cycles_t result;
	__asm__ __volatile__("rdtsc": "=A"(result));
	return result;
}
```

The following code show how to use current to calculate the time:
```C++
t1 = currentcycles();
sleep(1);
t2 = currentcycles();
printf("cou MHz：%lld/n", (t2-t1)/1000000);
```