/*
 * 对字符串转换为数字
 * 主要的是其中的异常情况指的注意。
 *
 */
int str2int(const char *str){
	int temp=0;
	const char *ptr= str;

	//如果有正负号则移至下一个字符。
	if(*str=='-'|| *str=='+')
		++str;
	while(*str!=0){
		if((*str<'0') || (*str>'9'))
			break;
		temp=temp*10+(*str-'0');
		str++;
	}
	if(*str=='-')
		temp=-temp;
	return temp;
}
