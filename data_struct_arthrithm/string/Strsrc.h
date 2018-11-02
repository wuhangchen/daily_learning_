//strstr库函数的实现，
//字符串中子串的查找


int Strstr(string haystack, string needle)
{
	if(needle.empty())
		return 0;
	int m=haystack.size();
	int n=needle.size();
	//意外情况，如果needle的长度比haystack的长度长，那么肯定是不能成功的。
	if(m<n)return -1;

	for(int i=0;i<=m-n;++i){
		int j=0;
		for(j=0;j<n;++j){
			if(haystack[i+j]!=needle[j])break;
		}
		if(j==n)return i;
	}
	return -i;
}
