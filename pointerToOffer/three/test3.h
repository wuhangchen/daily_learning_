namespace self{
	/*
	 * 数组中重复的数字。
	 * 在一个长度为n的数组里所有的数字都在0~n-1的范围内。数组中某些数字是重复的，返回是否
	 * 重复以及重复的数字是哪些。
	 */
	class solution{
		public:
			/*numbers表示数字，length表示长度，duplication表示重复的的范围。
			 * bool即返回是否重复
			 */
			bool duplicate(int numbers[],int length,int *duplication){
				if(numbers==nullptr || length<=0)
					return false;
				for(auto elems:numbers){
					if(elems<0 || elems>lenth-1)
						return false;
				}

				for(int i=0;i<length;++i){
					while(numbers[i]!=i){
						if(numbers[i] == numbers[numbers[i]]){
							*duplication = numbers[i];
							return true;
						}
						//是否可以利用移动语义呢？
						/*
						 *
						 */
						int temp = numbers[i];
						numbers[i] = numbers[temp];
						numbers[temp]=temp;
					}
				}
			}

	};
	
}
