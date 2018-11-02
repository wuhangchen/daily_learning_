//char *strcpy(char *strDest,const char *strSrc)
//同时需要额外的保证strDest 所指向的内存长度应该大于strSrc所指向的内存。

char* Strcpy(char* strDest,const char* strSrc)
{
	//意外情况的分析，
	if(strDest == nullptr || strSrc == nullptr)
		return nullptr;

	char *strDestCopy=strDest;
	while((*strDest++ = *strSrc++) != '\0');
	return strDestCopy;
}

//获取字符串的长度，同时并不包含最后的\o
//还可以进一部优化，利用2个指针的偏移来计算。
int get_string_len(const char* src){
	int len = 0;
	while(*src++ != '\0')
		++len;
	return len;
}

int get_string_len_version_2(const char *src)
{
	char *ptr=src;
	while(*ptr++ != '\0');
	return ptr-src;
}
