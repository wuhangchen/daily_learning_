/*2进制中1的个数
 *左移运算符(m<<n)表示把m左移n位，在左移n位的时候，最左边的n位将被丢弃，同时在最右边补上n个0
 *右移运算符(m>>n)表示把m右移n位，在右移动n的时候，最右边的n位将被舍弃，同时还需要判断是否是
 *有无符号数，对于无符号数，那么直接用0填充最左边的n位，如果数字是一个有符号数字，则使用数字的
 *符号位填充最左边的n位
 */


//可能会引起死循环的解法
int numberof1(int n){
	int count=0;
	while(n){
		if(n&1){
			count++;
			n=n>>1;
		}

	}
	return count;
}

//常规解法
int numberof1_version1(int n){
	int count = 0;
	unsigned int flag = 1;
	while(flag){
		if(n&flag)
			count++;
		flag = flag<<1;
	}
	return count;
}

//将一个整数减去1，在和原来的整数做与运算，会把该整数最右边的1变成0，那么一个整数的二进制表示中有多少个1就可以进行多少次这样的操作

int numberof1_version2(int n){
	int count = 0;
	while(n){
		++count;
		n=(n-1)&n;
	}
	return count;
}


