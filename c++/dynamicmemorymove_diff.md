

```c++
	void get_memory(char *p,int num){
		p=(char*)malloc(sizeof(char)*num);
	}

	int main()
	{
		char *str=nullptr;
		get_memory(str,10);
		
		strcpy(str,"hello");
		return 0;
	}	

```

实际上，getmemory并不能做任何事情，由于从getmemory中返回时不能获得堆中的内存的地址，那块堆内存也就不能继续引用，也就得不到释放，因此调用一次就会发生num byte的内存泄漏。
