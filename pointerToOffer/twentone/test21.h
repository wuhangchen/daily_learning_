/*
 *调整数组的顺序使得奇数位于偶数的前面。
 *使得所有的奇数位于数组的前面，而偶数位于数组的后半部分。
 *解决方案：利用双指针的行为
 */

void reorder_odd_event(int *pData,unsigned int length){
	if(pData==nullptr || length == 0)
		return ;
	int *pBegin = pData;
	int *pEnd = pData+length-1;
	while(pBegin<pEnd){
		//向后移动pBegin ,直到它指向偶数
		while(pBegin<pEnd && (*pBegin&0x1)!=0)
			pBegin++;
		//向前移动pEnd，知道它指向奇数。
		while(pBegin<pEnd && (*pEnd&0x1)==0)
			pEnd--;
		if(pBegin<pEnd){
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

//版本二，判断数字应该在数组前部分还是在后半部分的操作，
//二是拆分数组的操作
void reorder_odd_event_version1(int *pData,unsigned int length,bool (*func)(int)){
	if(pData == nullptr || length == 0)
		return ;
	int *pBegin = pData;
	int *pEnd = pData+length-1;
	while(pBegin<pEnd){
		while(pBegin<pEnd && !func(*pBegin))	
			pBegin++;
		while(pBegin<pEnd && func(*pEnd))
			pEnd--;
		if(pBegin<pEnd){
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

bool isEven(int n){
	return (n&1)==0;
}
