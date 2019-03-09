## unique_lock

The class unique_lock is a general-purpose mutex ownership wrapper allowing deferred locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with condition variables.

The class unique_lock is movable, but not copyable -- it meets the requirements of [MoveConstructible](https://en.cppreference.com/w/cpp/named_req/MoveConstructible) and [MoveAssignable](https://en.cppreference.com/w/cpp/named_req/MoveAssignable) but not of [CopyConstructible](https://en.cppreference.com/w/cpp/named_req/CopyConstructible) or [CopyAssignable](https://en.cppreference.com/w/cpp/named_req/CopyAssignable).

The class unique_lock meets the [BasicLockable](https://en.cppreference.com/w/cpp/named_req/BasicLockable) requirements. If **Mutex** meets the [Lockable](https://en.cppreference.com/w/cpp/named_req/Lockable) requirements, unique_lock also meets the [Lockable](https://en.cppreference.com/w/cpp/named_req/Lockable) requirements (ex.: can be used in [std::lock](https://en.cppreference.com/w/cpp/thread/lock)); if **Mutex** meets the [TimedLockable](https://en.cppreference.com/w/cpp/named_req/TimedLockable) requirements, unique_lock also meets the [TimedLockable](https://en.cppreference.com/w/cpp/named_req/TimedLockable) requirements.

### Template parameters

| Mutex | -    | the type of the mutex to lock. The type must meet the [BasicLockable](https://en.cppreference.com/w/cpp/named_req/BasicLockable) requirements |
| ----- | ---- | ------------------------------------------------------------ |
|       |      |                                                              |

### Member types

| Type         | Definition |
| ------------ | ---------- |
| `mutex_type` | Mutex      |

### Member functions

| [(constructor)](https://en.cppreference.com/w/cpp/thread/unique_lock/unique_lock) | constructs a `unique_lock`, optionally locking the supplied mutex  (public member function) |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [(destructor)](https://en.cppreference.com/w/cpp/thread/unique_lock/~unique_lock) | unlocks the associated mutex, if owned  (public member function) |
| [operator=](https://en.cppreference.com/w/cpp/thread/unique_lock/operator%3D) | unlocks the mutex, if owned, and acquires ownership of another  (public member function) |
| Locking                                                      |                                                              |
| [lock](https://en.cppreference.com/w/cpp/thread/unique_lock/lock) | locks the associated mutex  (public member function)         |
| [try_lock](https://en.cppreference.com/w/cpp/thread/unique_lock/try_lock) | tries to lock the associated mutex, returns if the mutex is not available  (public member function) |
| [try_lock_for](https://en.cppreference.com/w/cpp/thread/unique_lock/try_lock_for) | attempts to lock the associated [TimedLockable](https://en.cppreference.com/w/cpp/named_req/TimedLockable) mutex, returns if the mutex has been unavailable for the specified time duration  (public member function) |
| [try_lock_until](https://en.cppreference.com/w/cpp/thread/unique_lock/try_lock_until) | tries to lock the associated [TimedLockable](https://en.cppreference.com/w/cpp/named_req/TimedLockable) mutex, returns if the mutex has been unavailable until specified time point has been reached  (public member function) |
| [unlock](https://en.cppreference.com/w/cpp/thread/unique_lock/unlock) | unlocks the associated mutex  (public member function)       |
| Modifiers                                                    |                                                              |
| [swap](https://en.cppreference.com/w/cpp/thread/unique_lock/swap) | swaps state with another **std::unique_lock**  (public member function) |
| [release](https://en.cppreference.com/w/cpp/thread/unique_lock/release) | disassociates the associated mutex without unlocking it  (public member function) |
| Observers                                                    |                                                              |
| [mutex](https://en.cppreference.com/w/cpp/thread/unique_lock/mutex) | returns a pointer to the associated mutex  (public member function) |
| [owns_lock](https://en.cppreference.com/w/cpp/thread/unique_lock/owns_lock) | tests whether the lock owns its associated mutex  (public member function) |
| [operator bool](https://en.cppreference.com/w/cpp/thread/unique_lock/operator_bool) | tests whether the lock owns its associated mutex  (public member function) |

### Non-member functions

| [std::swap(std::unique_lock)](https://en.cppreference.com/w/cpp/thread/unique_lock/swap2)(C++11) | specialization of [std::swap](https://en.cppreference.com/w/cpp/algorithm/swap) for `unique_lock`  (function template) |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
|                                                              |                                                              |

### Example

Run this code

```
#include <mutex>
#include <thread>
#include <chrono>
 
struct Box {
    explicit Box(int num) : num_things{num} {}
 
    int num_things;
    std::mutex m;
};
 
void transfer(Box &from, Box &to, int num)
{
    // don't actually take the locks yet
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
 
    // lock both unique_locks without deadlock
    std::lock(lock1, lock2);
 
    from.num_things -= num;
    to.num_things += num;
 
    // 'from.m' and 'to.m' mutexes unlocked in 'unique_lock' dtors
}
 
int main()
{
    Box acc1(100);
    Box acc2(50);
 
    std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
    std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);
 
    t1.join();
    t2.join();
}
```
