## decltype

Sometimes we wish deducing the final type of an expression, but we do not want it to initialize the variable(use auto). To satisfy this requirement, C++11 intrduces **decltype**.

decltype is used to decude the expression type without call the expression or operate the expression.

Example:

```C++
int getSize();

int main(void)
{
    int tempA = 2;
    
    /*1.dclTempA为int*/
    decltype(tempA) dclTempA;
    /*2.dclTempB为int，对于getSize根本没有定义，但是程序依旧正常，因为decltype只做分析，并不调用getSize，*/
    decltype(getSize()) dclTempB;

    return 0;
}
```

#### decltype(auto)

If decltype(auto) is used for confirm the return type of an expression, the it has following processes,  

- replace the **auto** with expression
- reduce the expression type with the rule of "decltype"

