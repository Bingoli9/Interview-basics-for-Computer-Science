## lib function

### strcpy
```C++
char* strcpy(char* dest, const char* src)
{
	assert(NULL != des);
	assert(NULL != src);
	
	char *ptr;
	ptr = des;
	
	while ((*ptr++ = *src++) != '\0');
	return des;
}
```


### strlen
```C++
int strlen(const char* str)
{
	assert(NULL == str);
	int counter = 0;
	while (**str++ != '\0') {
		counter++;
	}
	return counter;
}
```


### memcpy
```C++
void* memcpy(void* dst, const void* src, size_t count)
{
	assert(dst && src);
	char* pdst = static_cast<char*>(dst_;
	const char* psrc = static_cast<const char*>(src);
	
	if ((pdst > psrc) && (psrc + count) > dst ) // memory overlap
	{
		for (int i = count-1; i != -1; --i)
		{
			pdst[i] = psrc[i];
		}
	}
	else 
	{
		fotr
	}
}
```