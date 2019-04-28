## Base64

Base64是基于64个可打印字符来表示二进制数据的表示方法，从本质上看是base64编码。

例如 "man" 用base64编码

<center>
  @<img src = "20130921153822859"/>
</center>

Base64编码表如下：

<center>
 @ <img src = "20130921153826093"/>
</center>



#### chromium中的base64

```C++
#include "./base64.h"
#include <string.h>
 
bool Base64Encode(const std::string& input, std::string* output) {
  std::string temp;
  temp.resize(modp_b64_encode_len(input.size()));  // makes room for null byte
 
  // null terminates result since result is base64 text!
  int input_size = static_cast<int>(input.size());
  int output_size= modp_b64_encode(&(temp[0]), input.data(), input_size);
  if (output_size < 0)
    return false;
 
  temp.resize(output_size);  // strips off null byte
  output->swap(temp);
  return true;
}
 
bool Base64Decode(const std::string& input, std::string* output) {
  std::string temp;
  temp.resize(modp_b64_decode_len(input.size()));
 
  // does not null terminate result since result is binary data!
  int input_size = static_cast<int>(input.size());
  int output_size = modp_b64_decode(&(temp[0]), input.data(), input_size);
  if (output_size < 0)
    return false;
 
  temp.resize(output_size);
  output->swap(temp);
  return true;
}
```

