
```c++ 
	#include<bits/stdc++.h>
	using namespace std;
	int main()
	{
		char *str[]={"welcome","to","fortemedia","nanjing",};
		char **p= str+1;
		str[0]=(*p++)+2;
		str[1]=*(p+1);
		str[2]=p[1]+3;
		str[3]=p[0]+(str[3]-str[1]);
		
		printf("%s\n",str[0]);
		printf("%s\n",str[1]);
		printf("%s\n",str[2]);
		printf("%s\n",str[3]);

		return 0;
	}
```

output:
(空)
nanjing
jing 
g

