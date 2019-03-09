## unordered_multimap

**unordered_m** is the map allows multiple keys. So, actually its operations are the same as **unordered_map**, except for extra operations for multi-key features.

The member function **at()** and **operator[]** is unusable for **unordered_multimap** due to the multi-key in **unordered_map**. The only choice is using member function **find()** and **equal_range()** to access element in **unordered_map**. 

```;
std::string key("jan");
auto n = people.count(key);

if (n==1) 
	std::cout << key << "is " << people.find(key)->second<<std::endl;
else {
    auto pr = people.equal_range(key);
    while (pr.first != pr.second) {
        std::cout << key << "is " << pr.first->second << std::endl;
        ++pr.first;
    }
}
```

#### insert element

```;
auto iter = people.emplace("jan", 45);
people.insert({"jan", 44});
people.emplace_hint(iter, "jan", 46);
```

