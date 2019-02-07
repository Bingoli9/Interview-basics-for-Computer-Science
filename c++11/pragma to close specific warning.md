## pragma to close specific warning

When using thirdparty api, usually there are some warning. If you want to close this warning which it's not your fault, you can use pragma to close specific warning.

#### In msvc

```C++
#ifdef _MSC_VER
// 关闭编译CImg.h时产生的警告
#pragma  warning( push ) 
#pragma  warning( disable: 4267 4319 )
#endif
#include "CImg.h"
#ifdef _MSC_VER
#pragma  warning(  pop  ) 
#endif
```

#### In gcc

```C++
#ifdef __GNUC__
// 关闭 using  _Base::_Base; 这行代码产生的警告
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winherited-variadic-ctor"
#endif
.....
namespace cimg_library {
template<typename T>
class CImgWrapper:public CImg<T> {
public:
    using   _Base =CImg<T>;
    using  _Base::_Base; // 继承基类构造函数
    ......
}
} /* namespace cimg_library */
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
```

