## sprintf
将格式化的数据写入字符串，可能会造成内存溢出

## snprintf

将格式化的数据写入字符串， 前n个字符。  
int snprintf(char* str, int n, char* format[, argument,..]);
返回值：成功则返回参数str字符串长度，失败则返回-1，错误原因存在于errno中  


