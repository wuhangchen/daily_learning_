//将字符串中个单词的翻转
//I am Shanghai
//Shanghai am I 

//先将每一个单词翻转一遍
//然后在整体的饭庄一遍

void rev_str(char *str)
{
	//维护3指针来执行遍历
	char *start = src;
	char *end = src;
	char *ptr = src;
	
	while(*ptr++ != '\0'){
		if(*ptr == ' ' || *ptr == '\0'){
			end = ptr-1;
		}
		while(start<end){
			std::swap(*start++,*end--);
		}
		start = end = ptr+1;
	}

	start = src,end = ptr-2;
	while(start<end){
		std::swap(*start++,*end--);
	}
}
