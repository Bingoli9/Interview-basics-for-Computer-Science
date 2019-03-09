## iconv
utf-8 转 GBK
···C++
int ret =0;
	size_t charInPutLen = input.length();
	if( charInPutLen == 0)
		return 0;
	char *pSource =(char *)input.c_str();
    size_t charOutPutLen = 2*charInPutLen;
	char *pTemp = new char[charOutPutLen];
	memset(pTemp,0,2*charInPutLen);
	
	iconv_t cd;
    char *pOut = pTemp ;
    cd = iconv_open("utf-8", "GBK");
    ret = iconv(cd, &pSource, &charInPutLen, &pTemp, &charOutPutLen);
    iconv_close(cd);
	output = pOut;
	delete []pOut;//注意这里，不能使用delete []pTemp, iconv函数会改变指针pTemp的值
	return ret;
```
