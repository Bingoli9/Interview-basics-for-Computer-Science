## string_cast

operator重载主要有两个作用

- 操作符重载
- 自定义对象类型的隐式转换

```C++
#include <iostream>
#include <sstream>                                                                                                                                                     
using namespace std;

class FuncObj
{
public:
  FuncObj(int n): _n(n) {
    cout << "constructor" << endl;
  }
  
  bool operator()(int v) {
    cout << "operator overload" << endl;
    return v > _n; 
  }

  operator string() {
    cout << "type convert" << endl;
    stringstream sstr;
    sstr << _n; 
    return sstr.str();
  }

  int _n; 
};

int main()
{
  FuncObj obj(10);
  if (obj(11))
    cout << "11 greater than 10" << endl;

  string str(obj);
  cout << str << endl;
}
```

#### string转其他类型

```C++
template <typename T>
  class string_cast
  {
  public:
    string_cast(const std::string &from): m_from(from) {
    }
    operator T() const {
      std::stringstream sstr(m_from);
      T ret;
      try {
        sstr >> ret;
      }
      catch(std::exception &e)
      {
         return T(0);
      }
      return ret;
    }
  private:
    const std::string &m_from;
  };
```







```C++
cout << string_cast<int>("123") << endl
```











