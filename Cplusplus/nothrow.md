## nothrow

In C, when using functions such as **malloc** to allocate memory, it is necessory to check whether the return value is a "NULL pointer" and take this as the basis to check whether the memory operation is successful. This form of test-for-null code is a good programming habit and necessary for writing reliable programs.

In C++, new by default throws an STD ::bad_alloc exception if the memory request fails.If this exception occurs, it means that the memory is exhausted, or there is some other reason for the memory allocation to fail.So, according to the C++ standard, if you want to check whether new succeeds, you should catch exceptions with a **try catch**.But some compilers do not support **try catch**.The C++ standardization committee doesn't want to yield **test-for-null** code, so they offer an alternative form of operator new, nothrow, to yield the traditional failure-null behavior.



```C++
#include "nothrow.hpp"
#include <iostream>
#include <new> // std::nothrow
 
// reference: http://www.cplusplus.com/reference/new/nothrow/
int test_nothrow1()
{
	std::cout << "Attempting to allocate 1 MiB...";
	char* p = new (std::nothrow) char[1048576];
	if (p == 0)
		std::cout << "Failed!\n";
	else {
		std::cout << "Succeeded!\n";
		delete[] p;
	}
 
	return 0;
}
 
// reference: http://en.cppreference.com/w/cpp/memory/new/nothrow
int test_nothrow2()
{
	try {
		while (true) {
			new int[100000000ul];   // throwing overload
		}
	}
	catch (const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
	}
 
	while (true) {
		int* p = new(std::nothrow) int[100000000ul]; // non-throwing overload
		if (p == nullptr) {
			std::cout << "Allocation returned nullptr\n";
			break;
		}
	}
 
	return 0;
}
```





