//在字符串上模拟数字加法的解法，
//打印从1到最大的n位数

void print_to_max_of_ndigits(int n){
	if(n<=0)
		return;
	char *number = new char[n+1];
	memset(number,'0',n);
	number[n]='\0';

	while(!increment(number)){
		print_number(number);
	}
	delete[] number;
}

bool increment(char *number){
	bool is_overflow = false;
	int n_takeover = 0;
	int length = strlen(number);

	for(int i=length-1;i>=0;--i){
		int n_sum = number[i]-'0'+n_takeover;
		if(i==length-1)
			n_sum++;
		if(n_sum>=10){
			if(i==0){
				is_overflow = true;
			}else{
				n_sum-=10;
				n_takeover = 1;
				number[i]='0'+n_sum;
			}
		}else{
			number[i]='0'+n_sum;
			break;
		}
	}
	return is_overflow;
}
//判断至第一个不为0的字符然后打印出来
void print_number(char *number){
	bool is_beginning0 = true;
	int n_length = strlen(number);

	for(int i=0;i<n_length;++i){
		if(is_beginning0 && number[i]!='0')
			is_beginning0 = false;
		if(!is_beginning0)
			printf("%c",number[i]);
	}
	printf("\n");
}
