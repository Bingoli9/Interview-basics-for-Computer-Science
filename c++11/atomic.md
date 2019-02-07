## atomic

#### std::atomic_flag

std::atomic_flag is an atomic bool type, it supports two atomic operation:

- test_and_set: if atomic_flag is set, the return true; if atomic_flag is not set, set it and return false;
- clear: clear atomic_flag 

std::atomic can be used for multi-threads synchronization. atomic_flag can be used to implement mutex.

```C++
#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>

std::atomic_flag lock = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_numer(int x)
{
  while (lock.test_and_set());
  stream << "thread#" << x << "\n";
  lock.clear();
}

int main()
{
  std::vector<std::thread> ths;
  for (int i=0; i<10; i++)
    ths.push_back(std::thread(append_numer, i));
  for (int i=0; i<10; i++)
    ths[i].join();
  std::cout << stream.str();
  return 0;
}
```

#### std::atomic

Std:: atomic encapsulates data structures such as int, char and bool atomically. In a multi-threaded environment, access to std:: atomic objects will not create competition-risk. The lock-free design of data structure can be realized by std:: atomic.

```C++
#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int i)
{
  while (!ready);
  for (int i=0; i<1000000; i++);
  if (!winner.test_and_set())
    std::cout << "winner: " << i << std::endl;
}

int main()
{
  std::vector<std::thread> ths;
  for (int i=0; i<10; i++)
    ths.push_back(std::thread(count1m, i));
  ready = true;
  for (int i=0; i<10; i++)
    ths[i].join();
  return 0;
}
```

