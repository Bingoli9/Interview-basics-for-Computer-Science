## C++11 STL

#### std::forward_list

STD ::forward_list is a linear table, which differs from list in that it is a one-direction linked list.

```C++
//示例代码1.0 http://www.cnblogs.com/feng-sc/p/5710724.html
#include <forward_list>
int main()
{
    std::forward_list<int> numbers = {1,2,3,4,5,4,4};
    std::cout << "numbers:" << std::endl;
    for (auto number : numbers)
    {
        std::cout << number << std::endl;
    }
    numbers.remove(4);
    std::cout << "numbers after remove:" << std::endl;
    for (auto number : numbers)
    {
        std::cout << number << std::endl;
    }
    return 0;
}
```

#### std::unordered_map

```C++
//webset address: http://www.cplusplus.com/reference/unordered_map/unordered_map/bucket_count/
#include <iostream>
#include <string>
#include <unordered_map>
int main()
{
    std::unordered_map<std::string, std::string> mymap =
    {
        { "house","maison" },
        { "apple","pomme" },
        { "tree","arbre" },
        { "book","livre" },
        { "door","porte" },
        { "grapefruit","pamplemousse" }
    };
    unsigned n = mymap.bucket_count();
    std::cout << "mymap has " << n << " buckets.\n";
    for (unsigned i = 0; i<n; ++i) 
    {
        std::cout << "bucket #" << i << " contains: ";
        for (auto it = mymap.begin(i); it != mymap.end(i); ++it)
            std::cout << "[" << it->first << ":" << it->second << "] ";
        std::cout << "\n";
    }
    return 0;
}
```

#### std::unordered_set

```C++
//示例代码1.0 http://www.cnblogs.com/feng-sc/p/5710724.html
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
int main()
{
    std::unordered_set<int> unorder_set;
    unorder_set.insert(7);
    unorder_set.insert(5);
    unorder_set.insert(3);
    unorder_set.insert(4);
    unorder_set.insert(6);
    std::cout << "unorder_set:" << std::endl;
    for (auto itor : unorder_set)
    {
        std::cout << itor << std::endl;
    }

    std::set<int> set;
    set.insert(7);
    set.insert(5);
    set.insert(3);
    set.insert(4);
    set.insert(6);
    std::cout << "set:" << std::endl;
    for (auto itor : set)
    {
        std::cout << itor << std::endl;
    }
}
```

