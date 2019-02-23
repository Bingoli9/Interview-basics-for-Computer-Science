## is_trivial

```C++
template< class T >
inline constexpr bool is_trivial_v = is_trivial<T>::value;
```

If T is TrivialType(that is, a scalar type, a trivially copyable class with a trivial default constructor, or array of such type/class, possibly cv-qualified), provides the member constant value equal true. For any other type, value is false.

The behavior is undefined if std::remove_all_extents_t\<T\> is an incomplete type and not (possibly cv-qualified)

