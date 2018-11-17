//各类排序算法

//快速排序
template<typename FwtIt,typename Compare=std::less<>>
void quick_sort(FwtIt first,FwtIt last,Compare cmp = Compare{})
{
	auto N = std::distance(first,last);
	if(N<=1)
		return;
	auto pivot = *next(first,N/2);
	auto middle1 = std::paration(first,last,[=](auto &elem){return cmp(elem,pivot );});
	auto middle2 = std::paration(first,last,[=](auto &elem){return !cmp(elem,pivot );});

	quick_sort(first,middle1,cmp);
	quick_sort(middle2,last,cmp);
}

//分配函数的用法，将数组中的数字分为2个部分，比选择数字小的数字移动到数组的左边，比选择数字大的数字移动到数组的右边
//返回的是风叉好的迭代器。
int Partition(int data[],int length,int start,int end)
{
	if(data == nullptr || length <= 0 || start <= 0 || end >= length)
		throw new std::exception("invalid parameters");
	int index = random_in_range(start,end);
	swap(&data[index],&data[end]);

	int small = start-1;//利用的是双指针
	for(index = start;index<end;++index){
		if(data[index]<data[end]){
			++small;
			if(small != index)
				swap(&data[index],&data[small]);
		}
	}
	++small;
	swap(&data[small],&data[end]);

	return small;
}
