## C++中string.find()函数与string::npos

查找字符串a是否包含字串b，

不是用strA.find(strB) > 0 而是strA.find(strB) == string :: npos 或者是

string::size_type pos == strA.find(strB); if(pos!=string::npos){}

npos是这样定义的：

static const size_type npos = -1; 因为string::size_type描述的是size，故需为无符号整数型别。因为缺省配置器以型别size_t作为size_type，于是-1被转换为无符号整数型别，npos也就成了该型别的最大无符号值。不过实际数值还是取决于型别 size_type 的实际定义。不幸的是这些最大值都不相同。事实上，(unsigned long)-1 和 (unsigned short)-1 不同(前提是两者型别大小不同)。因此，比较式 idx == string::npos 中，如果 idx 的值为-1，由于 idx 和字符串string::npos 型别不同，比较结果可能得到 false。
