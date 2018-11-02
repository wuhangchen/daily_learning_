//对于2个字符串A和B，返回公共的字符串
//A  "aocdfe"   B "pmcdfa"
//输出  "cdf"
//
char *commonstring(char *lhs,char *rhs)
{
	int i,j;
	char *shorter,*longer;
	char *substr;

	if(lhs==nullptr || rhs== nullptr)
		return nullptr;
	if(strlen(lhs)<=strlen(rhs)){
		shorter=lhs;
		longer=rhs;
	}else{
		shorter=rhs;
		longer=lhs;
	}

	//如果在长的字符串中能够直接的找到短字符串，那么直接返回段字符串
	if(strstr(longer,shorter) != nullptr)
		return shorter;
	substr = (char*)malloc(sizeof(char)*(strlen(shorter)+1));

	for(i=strlen(shorter)-1;i>0;--i){
		for(j=0;j<=strlen(shorter)-i;++j){
			memcpy(substr,&shorter[j],i-j);
			substr[i-j+1] = '\0';
			if(strstr(longer,substr)!=nullptr)
				return substr;
		}
	}

	return nullptr;

}

/*
 * aocdef   pmcdfa    
 *
 * i=5;j=0;substr=pmcdfa\0
 * i=5;j=1;substr=mcdfa\0
 *
