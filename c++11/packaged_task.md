## packaged_task

std::packaged_task function packs a async operation.

std::future function stores the result of async operation.

```C++
#include <iostream>
#include<vector>
#include <future>
using namespace std;

long long jiechen(int n)
{
    long long ret=1;
    for (int i=1;i<=n; i++)
        ret*=i;
    return ret;

}

int main()
{
    vector<int> data={9,11,13,17,19};
    vector<future<long long>> fus;
    for (auto i:data)
    {
        packaged_task<long long() > pt(bind(jiechen,i));
        fus.push_back(std::move(pt.get_future()));
        std::thread(std::move(pt)).detach();
    }
    for(auto& i:fus)
    {
        i.wait();
        cout<<i.get()<<endl;
    }
    return 0;
}
```



std::launch::async: create the thread when call **async**

std::launch::deferred: delays the creation of thread. Until call the **future** **get** or **wait** will create the thread.





