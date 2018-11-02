/*
 * 将整数转换字符串，将整数的各位上的数字加上'0'转换为char 类型并保存在字符数组中，然后在逆序
 * 保存一遍。
 */

//n为转换的数字，str为转换成的结果
void int2str(int n,char *str){
	//额外的保存空间的长度1000，如果发生越界，会导致未定义的行为。
	char buf[1000]="";
	int i=0;
	int len=0;
	//需要判断是否n为负数
	int temp = n<0?-n:n;
	if(str==nullptr)
		return ;
	while(temp){
		buf[i++]=(temp%10)+'0';
		temp=temp/10;
	}
	//如果有额外的负号那么我们需要额外的空间来保存。
	len = n<0?++i:i;
	while(true){
		i--;
		if(buf[len-i-1]==0)
			break;
		//将buf中的数字拷贝到字符串中
		str[i]=buf[len-i-1];
	}
	if(0==i)
		str[i]='-';
	
}

