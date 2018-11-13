namespace self{
	class soluction{
		/*
		 * 二维数组的查找，
		 * 每一行都按照从左到右递增的顺序排序，每一列都按照从上到下的的顺序排序。
		 * 判断是否二维数组中是否含有此数。
		 */
		bool find(int *matrix,int rows,int columns,int number){
			bool found = false;
			if(matrix!=nullptr && rows>0 && columns>0){
				int row=0;
				int column = columns-1;
				while(row<rows && column>=0){
					if(matrix[row*columns+column]==number){
						found = true;
						break;
					}else if(matrix[row*columns+column]>number){
						--column;
					}else{
						++row;
					}

				}
				return found;
			}


		}
	};
}
