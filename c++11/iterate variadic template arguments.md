## iterate variadic template arguments

```C++
template<size_t I = 0, typename FuncT, typename ...Tp>
inline typename std::enable_if_t<I == sizeof ...(Tp)>
for_each(std::tuple<Tp ...>&, FuncT)
{
}

template<size_t I = 0, typename FuncT, typename ...Tp>
inline typename std::enable_if_t<I < sizeof ...(Tp)>
for_each(std::tuple<Tp ...>& t, FuncT f)
{
    
}
template<typename ...Args>
auto print(Args ...args)
{
	auto a = std::forward_as_tuple(args...);
    for_each(a, [](auto x)
    {
    	std::cout << typeid(x).name() << ":" << x<< std::endl;             
    })
}
```

