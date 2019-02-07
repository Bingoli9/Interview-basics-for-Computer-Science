## pragma warning

\# pragma warning(push) store current compiler warning state

\# pragma warning(pop) restore original compiler warning state

```C++
#pragma warning(push)
#pragma warning(disable:4705)
#pragma warning(disable:4706)
#pragma warning (pop)
```

Using code above, 4705 and 4706 warning will disappear.