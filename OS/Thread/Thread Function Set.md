## Thread Function Set

| Number | Description                                      | Function               |
| ------ | ------------------------------------------------ | ---------------------- |
| 1      | create thread                                    | pthread_create         |
| 2      | wait for thread                                  | pthread_join           |
| 3      | detach the thread                                | pthread_detach         |
| 4      | create the thread's key                          | pthread_key_create     |
| 5      | delete the thread's key                          | pthread_key_delete     |
| 6      | set the thread's data                            | pthread_setspecific    |
| 7      | get the thread's data                            | pthread_getspecific    |
| 8      | get the thread's identity                        | pthread_self           |
| 9      | compare the thread                               | pthread_equal          |
| 10     | once execute                                     | pthread_once           |
| 11     | yield the cpu time                               | shed_yield             |
| 12     | change the thread's priority                     | pthread_setschedparam  |
| 13     | get the thread's priority                        | pthread_getshcedparam  |
| 14     | kill the thread                                  | pthread_kill           |
| 15     | set the thread's mask                            | pthread_sigmask        |
| 16     | teminate the thread                              | pthread_exit           |
| 17     | cancel the thread                                | pthread_cancel         |
| 18     | allow/forbid exit the thread                     | pthread_setcancelstate |
| 19     | set the exit type                                | pthread_setcanceltype  |
| 20     | create the point to exit the thread              | pthread_testcancel     |
| 21     | push the clean-up function when the thread exits | pthread_cleanup_push   |
| 22     | pop the clean-up function when the thread exits  | pthread_cleanup_pop    |

