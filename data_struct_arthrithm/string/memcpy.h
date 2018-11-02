//内存拷贝的实现
//需要注意dest所指向的内存必须大于size个单位，否则会发生越界的未定义的行为

void *Memcpy(void *dest,const void *src,size_t size)
{
	//考虑使用断言更好。
	if(dest == nullptr || src == nullptr)
		return nullptr;
	char *to_dest = (char *)dest;
	char *from_src = (char *)src;

	while(size-->0)
		*to_dest++ = *from_src++;
	return dest;
}
