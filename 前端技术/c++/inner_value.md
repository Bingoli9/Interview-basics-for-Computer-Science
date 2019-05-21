## inner_value

For POD type, if you want to remove reference, cv-qualificaitons adn decays  
function and arrays into pointers.  

```C++
template <typename T>
struct InnerType {
    using type = typename std::remove_cv<typename std::remove_reference<
        typename std::decay<T>::type>::type>::type;
}
```


